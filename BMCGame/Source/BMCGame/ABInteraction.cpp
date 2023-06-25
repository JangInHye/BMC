// Fill out your copyright notice in the Description page of Project Settings.


#include "ABInteraction.h"
#include "Components/SphereComponent.h"
#include "MyCharacter.h"

// Sets default values
AABInteraction::AABInteraction()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("TRIGGER"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	RootComponent = Trigger;
	Mesh->SetupAttachment(RootComponent);


	Trigger->SetCollisionProfileName(TEXT("Interaction"));
	Mesh->SetCollisionProfileName(TEXT("BlockAll"));

}

void AABInteraction::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AABInteraction::OnBeginCharacterOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AABInteraction::OnEndCharacterOverlap);
}

// Ʈ���� �浹 �� ó��
// ��ȣ�ۿ� �����ϸ� ���⼭ UI ����ֱ�.
void AABInteraction::OnBeginCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OnBeginCharacterOverlap"));

	// �÷��̾ ���� �浹���� ��ȣ�ۿ� ������Ʈ ���� �ѱ��
	AMyCharacter* myChar = (AMyCharacter*)OtherActor;
	myChar->OnInteractionStart(this);


}

// Ʈ���� �浹 ���� �� ó��
// ���� ����� UI�� �ִٸ� �����
void AABInteraction::OnEndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("OnEndCharacterOverlap"));

	// �÷��̾ �浹 �����ٰ� �˷��ֱ�
	AMyCharacter* myChar = (AMyCharacter*)OtherActor;
	myChar->OnInteractionEnd();


}

// E Ű�� ������ �� ó��
void AABInteraction::OnInteraction()
{
	UE_LOG(LogTemp, Warning, TEXT("OnInteraction In ABInteraction"));
}


//��ȣ�ۿ� ������Ʈ ������Ʈ Ÿ�� ��Ʈ������ ���
FString AABInteraction::GetInteractionType()
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("InteractionType"), true);
	if (!EnumPtr) return FString("Invalid");
	return EnumPtr->GetNameStringByIndex((int32)interactiontype);
}

