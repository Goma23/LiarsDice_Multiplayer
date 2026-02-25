#include "LiarsDicePlayerController.h"
#include "TimerManager.h"

ALiarsDicePlayerController::ALiarsDicePlayerController()
{
	bIsInteractionLocked = false;
}

void ALiarsDicePlayerController::RequestCheckDice()
{
	if (bIsInteractionLocked) return;

	// 상호작용 락 설정 (1.5초)
	bIsInteractionLocked = true;
	GetWorldTimerManager().SetTimer(LockTimerHandle, this, &ALiarsDicePlayerController::UnlockInteraction, 1.5f, false);

	// 서버에 통보하여 다른 플레이어들에게 애니메이션 전파
	Server_OnCheckDiceInteraction();
	
	// 로컬 카메라 애니메이션 트리거 (블루프린트 연동 예정)
}

void ALiarsDicePlayerController::Server_OnCheckDiceInteraction_Implementation()
{
	// 서버에서 모든 클라이언트에 해당 플레이어의 컵 드는 애니메이션 멀티캐스트 알림 로직
	UE_LOG(LogTemp, Warning, TEXT("Player %s is checking dice"), *GetName());
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
}
