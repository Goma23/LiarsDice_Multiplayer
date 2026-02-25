#pragma once

#include "CoreMinimal.h"
#include "LiarsDiceTypes.generated.h"

/** 게임의 현재 상태를 나타내는 열거형 */
UENUM(BlueprintType)
enum class ELiarsDiceGameState : uint8
{
	WaitingForPlayers    UMETA(DisplayName = "Waiting For Players"),
	MiniGame_DetermineOrder UMETA(DisplayName = "MiniGame: Determine Order"),
	MixingDice           UMETA(DisplayName = "Mixing Dice"),
	BettingRound         UMETA(DisplayName = "Betting Round"),
	RevealResults        UMETA(DisplayName = "Reveal Results"),
	GameOver             UMETA(DisplayName = "Game Over")
};

/** 베팅 정보를 나타내는 구조체 */
USTRUCT(BlueprintType)
struct FLiarsBetInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Liar's Dice")
	int32 Quantity;

	UPROPERTY(BlueprintReadWrite, Category = "Liar's Dice")
	int32 Value;

	UPROPERTY(BlueprintReadWrite, Category = "Liar's Dice")
	APlayerState* Better;

	FLiarsBetInfo()
		: Quantity(0), Value(0), Better(nullptr)
	{}
};

/** 플레이어들의 위치 데이터를 저장하는 구조체 */
USTRUCT(BlueprintType)
struct FSeatInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator Rotation;

	FSeatInfo()
		: Location(FVector::ZeroVector), Rotation(FRotator::ZeroRotator)
	{}
};
