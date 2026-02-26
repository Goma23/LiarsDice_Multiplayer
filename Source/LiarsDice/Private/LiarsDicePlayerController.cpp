#include "LiarsDicePlayerController.h"
#include "LiarsDiceGameMode.h"
#include "TimerManager.h"

ALiarsDicePlayerController::ALiarsDicePlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	bIsInteractionLocked = false;
	bIsCheckingDice = false;
	DefaultFOV = 90.0f;
	TargetFOV = 90.0f;
	ZoomSpeed = 10.0f;
}

void ALiarsDicePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateCamera(DeltaTime);
}

void ALiarsDicePlayerController::RequestCheckDice()
{
	if (bIsInteractionLocked) return;

	// 상호작용 락 설정 (1.5초)
	bIsInteractionLocked = true;
	bIsCheckingDice = true;
	TargetFOV = 55.0f; // 돋보기 줌 효과 (55도)

	GetWorldTimerManager().SetTimer(LockTimerHandle, this, &ALiarsDicePlayerController::UnlockInteraction, 1.5f, false);

	// 서버에 통보하여 다른 플레이어들에게 애니메이션 전파
	Server_OnCheckDiceInteraction();
}

void ALiarsDicePlayerController::StopCheckingDice()
{
	bIsCheckingDice = false;
	TargetFOV = DefaultFOV;
}

void ALiarsDicePlayerController::OnGameStateChanged(ELiarsDiceGameState NewState)
{
	if (NewState == ELiarsDiceGameState::RevealResults)
	{
		bIsShowingResults = true;
		TargetFOV = 70.0f; // 탑다운 결과 확인용 FOV
	}
	else if (NewState == ELiarsDiceGameState::MixingDice || NewState == ELiarsDiceGameState::BettingRound)
	{
		bIsShowingResults = false;
		TargetFOV = DefaultFOV;
	}
}

void ALiarsDicePlayerController::Server_OnCheckDiceInteraction_Implementation()
{
	// 서버에서 모든 클라이언트에 해당 플레이어의 컵 드는 애니메이션 멀티캐스트 알림
	UE_LOG(LogTemp, Warning, TEXT("Player %s is checking dice"), *GetName());
	Multicast_PlayCheckDiceAnimation();
}

void ALiarsDicePlayerController::Multicast_PlayCheckDiceAnimation_Implementation()
{
	// 모든 클라이언트에서 해당 플레이어 캐릭터의 애니메이션 블루프린트 트리거
	// (블루프린트에서 OnPlayCheckDiceAnimation 이벤트로 구현 예정)
	UE_LOG(LogTemp, Warning, TEXT("Multicast: Play check dice animation for %s"), *GetName());
}

void ALiarsDicePlayerController::Server_PlaceBet_Implementation(int32 Quantity, int32 Value)
{
	if (ALiarsDiceGameMode* GM = GetWorld()->GetAuthGameMode<ALiarsDiceGameMode>())
	{
		GM->HandleBet(this, Quantity, Value);
	}
}

void ALiarsDicePlayerController::Server_CallLiar_Implementation()
{
	if (ALiarsDiceGameMode* GM = GetWorld()->GetAuthGameMode<ALiarsDiceGameMode>())
	{
		GM->HandleLiar(this);
	}
}

void ALiarsDicePlayerController::UnlockInteraction()
{
	bIsInteractionLocked = false;
	UE_LOG(LogTemp, Warning, TEXT("Interaction Lock Released for %s"), *GetName());
	
	// 락이 풀렸을 때 자동으로 줌 해제할지 여부는 게임 디자인에 따라 결정
	// 여기서는 명시적인 StopCheckingDice 호출을 기다림
}

void ALiarsDicePlayerController::UpdateCamera(float DeltaTime)
{
	if (PlayerCameraManager)
	{
		float CurrentFOV = PlayerCameraManager->GetFOVAngle();
		if (!FMath::IsNearlyEqual(CurrentFOV, TargetFOV, 0.1f))
		{
			float NewFOV = FMath::FInterpTo(CurrentFOV, TargetFOV, DeltaTime, ZoomSpeed);
			PlayerCameraManager->SetFOV(NewFOV);
		}

		if (bIsShowingResults)
		{
			// 탑다운 90도 뷰로 부드럽게 회전 및 위치 보간 logic
			// (테이블 중앙 C+0,0,500 정도의 위치로 카메라 이동 유도)
			FRotator TargetRot = FRotator(-90.0f, 0.0f, 0.0f);
			FRotator CurrentRot = GetControlRotation();
			if (!CurrentRot.Equals(TargetRot, 0.1f))
			{
				SetControlRotation(FMath::RInterpTo(CurrentRot, TargetRot, DeltaTime, ZoomSpeed * 0.5f));
			}
		}
	}
}
