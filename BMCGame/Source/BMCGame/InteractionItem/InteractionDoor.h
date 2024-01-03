// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../LevelDataInstanceSubsystem.h"
#include "../InteractionItem/ABInteraction.h"
#include "InteractionDoor.generated.h"

	/// <summary>
	/// 이동하는 위치
	/// </summary>
UENUM(BlueprintType)
enum class EMoveToLevel : uint8
{
	E_Office UMETA(DisplayName = "Move To Office"),
	E_Delivery UMETA(DisplayName = "Move To Delivery"),
};
/**
 * 
 */
UCLASS()
class BMCGAME_API AInteractionDoor : public AABInteraction
{
	GENERATED_BODY()

public:
	AInteractionDoor();

		virtual void OnInteraction();
private:
	ULevelDataInstanceSubsystem* _levelData;	// 레벨 데이터

	UPROPERTY(EditAnywhere, Category = Camera)
		EMoveToLevel _moveToLevel = EMoveToLevel::E_Office;

	virtual void OnBeginCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)override;
	virtual void OnEndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)override;
};
