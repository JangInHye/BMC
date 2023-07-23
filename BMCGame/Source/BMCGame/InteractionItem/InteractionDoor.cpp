// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionDoor.h"
#include "../MyCharacter.h"
#include "Kismet/GameplayStatics.h"


AInteractionDoor::AInteractionDoor()
{
	AABInteraction::interactiontype = InteractionType::DOOR;
}

void AInteractionDoor::OnBeginCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMyCharacter* myChar = (AMyCharacter*)OtherActor;
	myChar->OnInteractionStart(this);
}


void AInteractionDoor::OnEndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMyCharacter* myChar = (AMyCharacter*)OtherActor;
	myChar->OnInteractionEnd();
}

// E Ű�� ������ �� ó��
void AInteractionDoor::OnInteraction()
{
	UGameplayStatics::OpenLevel(this, TEXT("DeliveryLevel"));
}

