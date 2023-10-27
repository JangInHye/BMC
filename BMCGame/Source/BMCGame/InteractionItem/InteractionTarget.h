// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../InteractionItem/ABInteraction.h"
#include "InteractionTarget.generated.h"

/**
 * 
 */
UCLASS()
class BMCGAME_API AInteractionTarget : public AABInteraction
{
	GENERATED_BODY()

public:
	AInteractionTarget();

	UPROPERTY(VisibleAnywhere, Category = Interaction)
		int _myID;
	
	virtual void OnInteraction();

private:
	virtual void OnBeginCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)override;
	virtual void OnEndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)override;
};
