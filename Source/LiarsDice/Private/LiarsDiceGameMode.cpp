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
}
