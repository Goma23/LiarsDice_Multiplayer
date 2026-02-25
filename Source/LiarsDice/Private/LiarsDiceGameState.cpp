#include "LiarsDiceGameState.h"

ALiarsDiceGameState::ALiarsDiceGameState()
{
	GameState = ELiarsDiceGameState::WaitingForPlayers;
	CurrentTurnIndex = 0;
}

void ALiarsDiceGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALiarsDiceGameState, GameState);
	DOREPLIFETIME(ALiarsDiceGameState, CurrentBet);
	DOREPLIFETIME(ALiarsDiceGameState, CurrentTurnIndex);
}
