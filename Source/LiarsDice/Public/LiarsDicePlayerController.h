#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LiarsDicePlayerController.generated.h"

UCLASS()
class LIARSDICE_API ALiarsDicePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ALiarsDicePlayerController();

	/** 주사위 확인 시도 (쿨다운 포함) */
	UFUNCTION(BlueprintCallable, Category = "GameFlow")
	void RequestCheckDice();

	/** 서버에 주사위 확인 애니메이션 동기화 요청 */
	UFUNCTION(Server, Reliable, Category = "GameFlow")
	void Server_OnCheckDiceInteraction();

	/** 서버에 베팅 요청 */
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "GameFlow")
	void Server_PlaceBet(int32 Quantity, int32 Value);

	/** 서버에 거짓말 선언 요청 */
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "GameFlow")
	void Server_CallLiar();

protected:
	/** 상호작용 락 상태 */
	bool bIsInteractionLocked;

	/** 락 해제 타이머 핸들 */
	FTimerHandle LockTimerHandle;

	/** 락 해제 함수 */
	void UnlockInteraction();
};
