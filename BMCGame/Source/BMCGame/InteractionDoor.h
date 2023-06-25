// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABInteraction.h"
#include "InteractionDoor.generated.h"

/**
 * 
 */
UCLASS()
class BMCGAME_API AInteractionDoor : public AABInteraction
{
	GENERATED_BODY()

public:
	AInteractionDoor();
private:
	virtual void OnBeginCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)override;
	virtual void OnEndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)override;
	
};
