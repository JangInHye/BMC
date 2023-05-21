// Fill out your copyright notice in the Description page of Project Settings.


#include "ABInteraction.h"
#include "Components/SphereComponent.h"

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

void AABInteraction::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Interaction"), EInputEvent::IE_Pressed, this, &AABInteraction::OnInteraction);
}

// Ʈ���� �浹 �� ó��
// ��ȣ�ۿ� �����ϸ� ���⼭ UI ����ֱ�.
void AABInteraction::OnBeginCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IsOverlap = true;
	UE_LOG(LogTemp, Warning, TEXT("OnBeginCharacterOverlap"));
}

// Ʈ���� �浹 ���� �� ó��
// ���� ����� UI�� �ִٸ� �����
void AABInteraction::OnEndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	IsOverlap = false;
	UE_LOG(LogTemp, Warning, TEXT("OnEndCharacterOverlap"));
}

// E Ű�� ������ �� ó��
void AABInteraction::OnInteraction()
{
	if (IsOverlap)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnInteraction"));
	}
}
