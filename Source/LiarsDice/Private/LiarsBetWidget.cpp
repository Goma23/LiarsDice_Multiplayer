#include "LiarsBetWidget.h"
#include "LiarsDicePlayerController.h"

void ULiarsBetWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	SelectedQuantity = 1;
	SelectedValue = 2; // 기본값 (1은 와일드카드)
}

void ULiarsBetWidget::ConfirmBet()
{
	if (ALiarsDicePlayerController* PC = Cast<ALiarsDicePlayerController>(GetOwningPlayer()))
	{
		PC->Server_PlaceBet(SelectedQuantity, SelectedValue);
	}
}

void ULiarsBetWidget::AdjustQuantity(int32 Delta)
{
	SelectedQuantity = FMath::Clamp(SelectedQuantity + Delta, 1, 25); // 최대 25개(5인 기준)
	// UI 텍스트 업데이트 로직 블루프린트 호출 예정
}

void ULiarsBetWidget::AdjustValue(int32 NewValue)
{
	if (NewValue >= 2 && NewValue <= 6)
	{
		SelectedValue = NewValue;
	}
}

void ULiarsBetWidget::CallLiar()
{
	if (ALiarsDicePlayerController* PC = Cast<ALiarsDicePlayerController>(GetOwningPlayer()))
	{
		PC->Server_CallLiar();
		// UI 비활성화 연출 등 추가 예정
	}
}
