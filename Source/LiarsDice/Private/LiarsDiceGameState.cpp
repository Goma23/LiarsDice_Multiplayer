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

void ALiarsDiceGameState::OnRep_GameState()
{
	// 클라이언트 측에서 상태 변경 시 로컬 연출 트리거
	if (ALiarsDicePlayerController* PC = Cast<ALiarsDicePlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		PC->OnGameStateChanged(GameState);
	}
}
