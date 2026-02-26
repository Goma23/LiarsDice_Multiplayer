#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LiarsDiceTable.generated.h"

/** 게임의 중심이 되는 테이블 액터 */
UCLASS()
class LIARSDICE_API ALiarsDiceTable : public AActor
{
	GENERATED_BODY()
	
public:	
	ALiarsDiceTable();

protected:
	virtual void BeginPlay() override;

	/** 테이블 메시 */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* TableMesh;

	/** 플레이어 좌석 위치 프리셋 (컴포넌트로 관리 가능) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Seating")
	TArray<USceneComponent*> SeatMarkers;

public:	
	/** 특정 인덱스의 좌석 변환값 반환 */
	UFUNCTION(BlueprintCallable, Category = "Seating")
	FTransform GetSeatTransform(int32 Index) const;
};
