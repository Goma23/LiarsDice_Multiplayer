#include "LiarsDicePlayerState.h"

ALiarsDicePlayerState::ALiarsDicePlayerState()
{
	RemainingDiceCount = 5;
	MiniGameRollValue = 0;
}

void ALiarsDicePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALiarsDicePlayerState, DiceValues);
	DOREPLIFETIME(ALiarsDicePlayerState, RemainingDiceCount);
	DOREPLIFETIME(ALiarsDicePlayerState, MiniGameRollValue);
	DOREPLIFETIME(ALiarsDicePlayerState, HighlightedDiceIndices);
}

void ALiarsDicePlayerState::Server_RollMiniGameDie_Implementation()
{
	MiniGameRollValue = FMath::RandRange(1, 6);
	
	// GameMode에게 보고 (미니게임 진행 중일 때만 유효)
}
