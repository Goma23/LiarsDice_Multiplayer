#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"
#include "LiarsDicePlayerState.generated.h"

UCLASS()
class LIARSDICE_API ALiarsDicePlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ALiarsDicePlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "GameRules")
	TArray<int32> DiceValues;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "GameRules")
	int32 RemainingDiceCount;
};
