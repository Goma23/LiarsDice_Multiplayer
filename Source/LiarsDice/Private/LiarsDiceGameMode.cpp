#include "LiarsDiceGameMode.h"
#include "LiarsDiceGameState.h"
#include "LiarsDicePlayerState.h"

ALiarsDiceGameMode::ALiarsDiceGameMode()
{
	GameStateClass = ALiarsDiceGameState::StaticClass();
	PlayerStateClass = ALiarsDicePlayerState::StaticClass();
	TableRadius = 200.0f; // 기본 반경 설정
}

void ALiarsDiceGameMode::BeginPlay()
{
	Super::BeginPlay();
	SetCurrentGameState(ELiarsDiceGameState::WaitingForPlayers);
}

void ALiarsDiceGameMode::SetCurrentGameState(ELiarsDiceGameState NewState)
{
	if (ALiarsDiceGameState* GS = GetGameState<ALiarsDiceGameState>())
	{
		GS->GameState = NewState;
		UE_LOG(LogTemp, Warning, TEXT("Game State Changed to: %d"), (int32)NewState);
	}
}

void ALiarsDiceGameMode::CheckAllPlayersReady()
{
	// 인원 체크 로직 (최고 2명) 후 MiniGame_DetermineOrder 상태로 전환 예정
}

TArray<FSeatInfo> ALiarsDiceGameMode::CalculateSeatPositions(int32 PlayerCount)
{
	TArray<FSeatInfo> Result;
	if (PlayerCount < 2) return Result;

	float AngleStep = 360.0f / PlayerCount;
	
	// 2명일 경우 서로 마주보게 (180도), 3명 이상은 다각형 형태
	for (int32 i = 0; i < PlayerCount; ++i)
	{
		float CurrentAngle = i * AngleStep;
		float AngleRad = FMath::DegreesToRadians(CurrentAngle);

		FSeatInfo NewSeat;
		// X = R * cos(theta), Y = R * sin(theta)
		NewSeat.Location = FVector(FMath::Cos(AngleRad) * TableRadius, FMath::Sin(AngleRad) * TableRadius, 0.0f);
		
		// 테이블 중앙을 바라보게 회전값 계산
		NewSeat.Rotation = (FVector::ZeroVector - NewSeat.Location).Rotation();
		
		Result.Add(NewSeat);
	}

	return Result;
}
