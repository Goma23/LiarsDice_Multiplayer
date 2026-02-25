#include "LiarsDiceGameState.h"

ALiarsDiceGameState::ALiarsDiceGameState()
{
	CurrentTurnIndex = 0;
	LastQuantity = 0;
	LastValue = 0;
}

void ALiarsDiceGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALiarsDiceGameState, CurrentTurnIndex);
	DOREPLIFETIME(ALiarsDiceGameState, LastQuantity);
	DOREPLIFETIME(ALiarsDiceGameState, LastValue);
}
