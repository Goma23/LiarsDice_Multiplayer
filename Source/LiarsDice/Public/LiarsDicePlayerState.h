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
	int32 RemainingDiceCount;

	/** 미니게임(순서 정하기)에서 굴린 숫자 */
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "GameRules")
	int32 MiniGameRollValue;

	/** 서버에서 주사위를 굴립니다. */
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "GameRules")
	void Server_RollMiniGameDie();
};
