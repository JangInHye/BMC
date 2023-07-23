// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/Pawn.h"
#include "ABInteraction.generated.h"


UENUM(BlueprintType)
enum class InteractionType : uint8
{
	NONE UMETA(FDisplayNameEntryId ="None"),
	DOOR UMETA(FDisplayNameEntryId = "Door"),
    BED UMETA(FDisplayNameEntryId = "Bed"),
	STORAGE UMETA(FDisplayNameEntryId="Storage"),
};


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



	UPROPERTY(EditAnywhere, Category = Interaction)
		InteractionType interactiontype= InteractionType::NONE;

	UFUNCTION()
		virtual void OnInteraction();
	UFUNCTION()
		virtual FString GetInteractionType();

private:
	UFUNCTION()
		virtual void OnBeginCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		virtual void OnEndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
