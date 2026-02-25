#include "LiarsDicePlayerState.h"

ALiarsDicePlayerState::ALiarsDicePlayerState()
{
	RemainingDiceCount = 5;
}

void ALiarsDicePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALiarsDicePlayerState, DiceValues);
	DOREPLIFETIME(ALiarsDicePlayerState, RemainingDiceCount);
}
