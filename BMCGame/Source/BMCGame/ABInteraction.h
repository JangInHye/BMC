// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/Pawn.h"
#include "Components/WidgetComponent.h"
#include "ABInteraction.generated.h"

UCLASS()
class BMCGAME_API AABInteraction : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABInteraction();

protected:
	virtual void PostInitializeComponents() override;

public:
	UPROPERTY(VisibleAnywhere, Category = Interaction)
		UShapeComponent* Trigger;

	UPROPERTY(EditAnywhere, Category = Interaction)
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = UI)
		class UWidgetComponent* InteractionWidget;

	UFUNCTION()
		virtual void OnInteraction();
private:
	UFUNCTION()
		virtual void OnBeginCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		virtual void OnEndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
