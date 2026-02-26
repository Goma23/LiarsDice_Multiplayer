#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Net/UnrealNetwork.h"
#include "LiarsDiceTypes.h"
#include "LiarsDiceGameState.generated.h"

UCLASS()
class LIARSDICE_API ALiarsDiceGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ALiarsDiceGameState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(ReplicatedUsing = OnRep_GameState, BlueprintReadOnly, Category = "GameRules")
	ELiarsDiceGameState GameState;

	UFUNCTION()
	void OnRep_GameState();

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "GameRules")
	FLiarsBetInfo CurrentBet;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "GameRules")
	int32 CurrentTurnIndex;
};
