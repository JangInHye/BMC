// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionTarget.h"
#include "Kismet/GameplayStatics.h"


AInteractionTarget::AInteractionTarget()
{
	AABInteraction::interactiontype = InteractionType::DOOR;
}

void AInteractionTarget::OnBeginCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	_myChar = (AMyCharacter*)OtherActor;
	_myChar->OnInteractionStart(this);
}


void AInteractionTarget::OnEndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	_myChar = (AMyCharacter*)OtherActor;
	_myChar->OnInteractionEnd();
}

// E Ű�� ������ �� ó��
// ����Ʈ ó��
void AInteractionTarget::OnInteraction()
{
	if (_myChar == nullptr) return;

	// ����Ʈ ����� �´��� üũ

	// ����Ʈ ����̶�� �ش� ����Ʈ ó��
	_myChar->QuestClear(_myID);
}