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

// E 키를 눌렀을 때 처리
// 퀘스트 처리
void AInteractionTarget::OnInteraction()
{
	if (_myChar == nullptr) return;

	// 퀘스트 대상이 맞는지 체크

	// 퀘스트 대상이라면 해당 퀘스트 처리
	_myChar->QuestClear(_myID);
}