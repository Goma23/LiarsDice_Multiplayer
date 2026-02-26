#include "LiarsDiceTable.h"

ALiarsDiceTable::ALiarsDiceTable()
{
	PrimaryActorTick.bCanEverTick = false;

	TableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TableMesh"));
	RootComponent = TableMesh;
	
	// 기본 시트 마커 5개 생성 (2~5인용)
	for (int32 i = 0; i < 5; ++i)
	{
		FString MarkerName = FString::Printf(TEXT("SeatMarker_%d"), i);
		USceneComponent* Marker = CreateDefaultSubobject<USceneComponent>(*MarkerName);
		Marker->SetupAttachment(RootComponent);
		SeatMarkers.Add(Marker);
	}
}

void ALiarsDiceTable::BeginPlay()
{
	Super::BeginPlay();
}

FTransform ALiarsDiceTable::GetSeatTransform(int32 Index) const
{
	if (SeatMarkers.IsValidIndex(Index))
	{
		return SeatMarkers[Index]->GetComponentTransform();
	}
	return GetActorTransform();
}
