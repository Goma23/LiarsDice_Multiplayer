#include "LiarsDiceGameMode.h"
#include "LiarsDiceGameState.h"
#include "LiarsDicePlayerState.h"

ALiarsDiceGameMode::ALiarsDiceGameMode()
{
	GameStateClass = ALiarsDiceGameState::StaticClass();
	PlayerStateClass = ALiarsDicePlayerState::StaticClass();
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
	// 인원 체크 로직 (최소 2명) 후 MiniGame_DetermineOrder 상태로 전환 예정
}
