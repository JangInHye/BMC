// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionStorage.h"
#include "MyCharacter.h"

AInteractionStorage::AInteractionStorage()
{
	AABInteraction::interactiontype = InteractionType::STORAGE;
}

void AInteractionStorage::OnBeginCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMyCharacter* myChar = (AMyCharacter*)OtherActor;
	myChar->OnInteractionStart(this);
}

void AInteractionStorage::OnEndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMyCharacter* myChar = (AMyCharacter*)OtherActor;
	myChar->OnInteractionEnd();
}
