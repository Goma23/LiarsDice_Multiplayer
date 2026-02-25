#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LiarsDiceTypes.h"
#include "LiarsDiceGameMode.generated.h"

UCLASS()
class LIARSDICE_API ALiarsDiceGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALiarsDiceGameMode();

	/** 원형 테이블의 반경 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float TableRadius;

	/** 플레이어 인원수에 따른 좌석 정보 계산 */
	UFUNCTION(BlueprintCallable, Category = "GameFlow")
	TArray<FSeatInfo> CalculateSeatPositions(int32 PlayerCount);

protected:
	virtual void BeginPlay() override;

public:
	/** 현재 게임 상태를 전환합니다. */
	void SetCurrentGameState(ELiarsDiceGameState NewState);

	/** 모든 플레이어의 연결이 완료되었는지 확인합니다. */
	UFUNCTION(BlueprintCallable, Category = "GameFlow")
	void CheckAllPlayersReady();
};
