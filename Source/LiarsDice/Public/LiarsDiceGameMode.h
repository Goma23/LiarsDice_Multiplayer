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

	/** 현재 게임에 참여 중인 플레이어 목록 */
	UPROPERTY(BlueprintReadOnly, Category = "GameFlow")
	TArray<APlayerController*> JoinedPlayers;

	/** 각 플레이어에게 할당된 좌석 정보 */
	UPROPERTY(BlueprintReadOnly, Category = "GameFlow")
	TMap<APlayerController*, FSeatInfo> PlayerSeatMap;

protected:
	virtual void BeginPlay() override;

public:
	/** 현재 게임 상태를 전환합니다. */
	void SetCurrentGameState(ELiarsDiceGameState NewState);

	/** 모든 플레이어의 연결이 완료되었는지 확인합니다. */
	UFUNCTION(BlueprintCallable, Category = "GameFlow")
	void CheckAllPlayersReady();

	/** 플레이어 접속 시 호출되는 가상 함수 재정의 */
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	/** 모든 플레이어를 계산된 위치로 재배치합니다. */
	void RedistributePlayers();

	/** 플레이어의 베팅 요청을 처리합니다. */
	void HandleBet(APlayerController* Player, int32 Quantity, int32 Value);

	/** 플레이어의 거짓말 선언 요청을 처리합니다. */
	void HandleLiar(APlayerController* Player);

	/** 다음 플레이어로 턴을 넘깁니다. */
	void AdvanceTurn();

	/** 승패 판정 및 주사위 차감 처리 */
	void ResolveMatch();

	/** 새로운 라운드를 시작합니다. */
	void StartNewRound();

	/** 모든 플레이어의 주사위를 랜덤하게 설정합니다. */
	void RollDiceForAllPlayers();

	/** 미니게임 결과 집계 */
	void ProcessMiniGameResults();

	/** 순서 결정권을 가진 플레이어 설정 */
	void SetOrderAuthority(APlayerController* Winner);

	/** 게임 진행 방향 설정 (시계/반시계) */
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "GameFlow")
	void Server_SetGameDirection(bool bIsClockwise);

private:
	/** 미니게임 동점자 목록 */
	TArray<APlayerController*> MiniGameTiedPlayers;
	
	/** 게임 방향 (true: 시계, false: 반시계) */
	bool bClockwise;
};
