// Fill out your copyright notice in the Description page of Project Settings.


#include "ABInteraction.h"
#include "Components/SphereComponent.h"

// Sets default values
AABInteraction::AABInteraction()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("TRIGGER"));

	RootComponent = Trigger;

	Trigger->SetCollisionProfileName(TEXT("Interaction"));
}

// Called when the game starts or when spawned
void AABInteraction::BeginPlay()
{
	Super::BeginPlay();
	
}

void AABInteraction::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AABInteraction::OnCharacterOverlap);
}

void AABInteraction::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("WARNING"));
}
