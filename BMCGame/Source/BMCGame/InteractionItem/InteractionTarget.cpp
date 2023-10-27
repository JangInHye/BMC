// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionTarget.h"
#include "../MyCharacter.h"
#include "Kismet/GameplayStatics.h"


AInteractionTarget::AInteractionTarget()
{
	AABInteraction::interactiontype = InteractionType::DOOR;
}

void AInteractionTarget::OnBeginCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMyCharacter* myChar = (AMyCharacter*)OtherActor;
	myChar->OnInteractionStart(this);
}


void AInteractionTarget::OnEndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMyCharacter* myChar = (AMyCharacter*)OtherActor;
	myChar->OnInteractionEnd();
}

// E Ű�� ������ �� ó��
// ����Ʈ ó��
void AInteractionTarget::OnInteraction()
{
	// ����Ʈ ����� �´��� üũ

	// ����Ʈ ����̶�� �ش� ����Ʈ ó��
}