#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LiarsDiceNPC.generated.h"

/** 술집 테마를 완성할 NPC 클래스 */
UCLASS()
class LIARSDICE_API ALiarsDiceNPC : public ACharacter
{
	GENERATED_BODY()

public:
	ALiarsDiceNPC();

	/** 게임 상태 변화에 따른 감정/동작 반응 */
	UFUNCTION(BlueprintImplementableEvent, Category = "NPC")
	void OnGameEvent(const FString& EventName);

	/** "거짓말!" 선언 시 놀라는 동작 */
	UFUNCTION(BlueprintCallable, Category = "NPC")
	void ReactToLiarCall();

protected:
	virtual void BeginPlay() override;
};
