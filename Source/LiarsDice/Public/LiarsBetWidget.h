#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LiarsBetWidget.generated.h"

/** 타원형 베팅 UI의 베이스 클래스 */
UCLASS()
class LIARSDICE_API ULiarsBetWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** 현재 선택된 주사위 수량 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Betting")
	int32 SelectedQuantity;

	/** 현재 선택된 주사위 숫자 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Betting")
	int32 SelectedValue;

	/** 베팅 확인 버튼 클릭 시 호출 */
	UFUNCTION(BlueprintCallable, Category = "Betting")
	void ConfirmBet();

	/** "거짓말!" 버튼 클릭 시 호출 */
	UFUNCTION(BlueprintCallable, Category = "Betting")
	void CallLiar();

protected:
	/** 초기화 로직 */
	virtual void NativeConstruct() override;
};
