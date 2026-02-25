#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LiarsDiceGameMode.generated.h"

UCLASS()
class LIARSDICE_API ALiarsDiceGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALiarsDiceGameMode();

protected:
	virtual void BeginPlay() override;

	// 게임 세션 및 플레이어 관리 로직 추가 예정
};
