// Fill out your copyright notice in the Description page of Project Settings.


#include "ABInteraction.h"
#include <Blueprint/UserWidget.h>
#include "Components/SphereComponent.h"

// Sets default values
AABInteraction::AABInteraction()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("TRIGGER"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("INTERACTION_UI"));

	RootComponent = Trigger;
	Mesh->SetupAttachment(RootComponent);
	InteractionWidget->SetupAttachment(RootComponent);

	Trigger->SetCollisionProfileName(TEXT("Interaction"));
	Mesh->SetCollisionProfileName(TEXT("BlockAll"));
	InteractionWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);
	static  ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Game/Dummy/UMG/UMG_Interaction"));
	if (UI_HUD.Succeeded()) 
	{
		InteractionWidget->SetWidgetClass(UI_HUD.Class);
		InteractionWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
		InteractionWidget->SetVisibility(false);

    }

	

	//
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

// 트리거 충돌 시 처리
// 상호작용 가능하면 여기서 UI 띄워주기.
void AABInteraction::OnBeginCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IsOverlap = true;
	UE_LOG(LogTemp, Warning, TEXT("OnBeginCharacterOverlap"));
	InteractionWidget->SetVisibility(true);
}

// 트리거 충돌 종료 시 처리
// 위에 띄워준 UI가 있다면 지우기
void AABInteraction::OnEndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	IsOverlap = false;
	UE_LOG(LogTemp, Warning, TEXT("OnEndCharacterOverlap"));
	InteractionWidget->SetVisibility(false);

}

// E 키를 눌렀을 때 처리
void AABInteraction::OnInteraction()
{
	if (IsOverlap)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnInteraction"));
	}
}
