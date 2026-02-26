#include "LiarsDiceNPC.h"

ALiarsDiceNPC::ALiarsDiceNPC()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALiarsDiceNPC::BeginPlay()
{
	Super::BeginPlay();
}

void ALiarsDiceNPC::ReactToLiarCall()
{
	// 블루프린트에서 애니메이션을 트리거할 수 있도록 이벤트 호출
	OnGameEvent(TEXT("LiarCalled"));
}
