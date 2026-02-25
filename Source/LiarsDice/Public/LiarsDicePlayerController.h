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

	virtual void Tick(float DeltaTime) override;

	/** 베팅 확인 버튼 클릭 시 호출 */
	UFUNCTION(BlueprintCallable, Category = "Betting")
	void ConfirmBet();

	/** 다이얼을 돌려 수량을 변경합니다. */
	UFUNCTION(BlueprintCallable, Category = "Betting")
	void AdjustQuantity(int32 Delta);

	/** 주사위 숫자를 변경합니다. */
	UFUNCTION(BlueprintCallable, Category = "Betting")
	void AdjustValue(int32 NewValue);

	/** 주사위 확인 시도 (쿨다운 포함) */
	UFUNCTION(BlueprintCallable, Category = "GameFlow")
	void RequestCheckDice();

	/** "거짓말!" 버튼 클릭 시 호출 */
	UFUNCTION(BlueprintCallable, Category = "GameFlow")
	void StopCheckingDice();

	/** 서버에 주사위 확인 애니메이션 동기화 요청 */
	UFUNCTION(Server, Reliable, Category = "GameFlow")
	void Server_OnCheckDiceInteraction();

	/** 모든 클라이언트에 주사위 확인 애니메이션 재생 알림 */
	UFUNCTION(NetMulticast, Reliable, Category = "GameFlow")
	void Multicast_PlayCheckDiceAnimation();

	/** 서버에 베팅 요청 */
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "GameFlow")
	void Server_PlaceBet(int32 Quantity, int32 Value);

	/** 서버에 거짓말 선언 요청 */
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "GameFlow")
	void Server_CallLiar();

protected:
	/** 상호작용 락 상태 */
	bool bIsInteractionLocked;

	/** 현재 주사위를 확인 중인지 여부 */
	bool bIsCheckingDice;

	/** 카메라 FOV 보간 목표값 */
	float TargetFOV;
	float DefaultFOV;

	/** 줌 속도 */
	UPROPERTY(EditAnywhere, Category = "Camera")
	float ZoomSpeed;

	/** 락 해제 타이머 핸들 */
	FTimerHandle LockTimerHandle;

	/** 락 해제 함수 */
	void UnlockInteraction();

	/** 카메라 업데이트 로직 */
	void UpdateCamera(float DeltaTime);
};
