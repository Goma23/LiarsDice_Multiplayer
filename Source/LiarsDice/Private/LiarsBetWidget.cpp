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
		// UI 비활성화 연출 등 추가 예정
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
