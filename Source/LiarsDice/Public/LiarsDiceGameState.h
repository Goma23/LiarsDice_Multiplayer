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

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "GameRules")
	ELiarsDiceGameState GameState;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "GameRules")
	FLiarsBetInfo CurrentBet;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "GameRules")
	int32 CurrentTurnIndex;
};
