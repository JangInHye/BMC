// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include <Blueprint/UserWidget.h>
#include "UI/UI_InteractionKey.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRIGNARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("UI_INTERACTION"));
	InventoryWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("UI_INVENTORY"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);
	InteractionWidget->SetupAttachment(RootComponent);
	InventoryWidget->SetupAttachment(RootComponent);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));
	InteractionWidget->SetRelativeLocation(FVector(0.0f,0.0f,130.0f));
	InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);
	InventoryWidget->SetWidgetSpace(EWidgetSpace::Screen);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT("/Game/Dummy/Characters/Mannequins/Meshes/SKM_Manny"));
	if (SK_CARDBOARD.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_CARDBOARD.Object);
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> WARRIOR_ANIM(TEXT("/Game/Dummy/Characters/Mannequins/Animations/Manny/WarriorAnimBlueprint.WarriorAnimBlueprint_C"));
	if (WARRIOR_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(WARRIOR_ANIM.Class);
	}

	static  ConstructorHelpers::FClassFinder<UUI_InteractionKey> UI_InteractionHUD(TEXT("/Game/Dummy/UMG/UMG_Interaction"));
	if (UI_InteractionHUD.Succeeded())
	{
		InteractionWidget->SetWidgetClass(UI_InteractionHUD.Class);
		InteractionWidget->SetDrawSize(FVector2D(140.0f, 20.0f));
		InteractionWidget->SetVisibility(false);
	}

	static ConstructorHelpers::FClassFinder<UUI_Inveotory> UI_InventoryHUD(TEXT("/Game/Dummy/UMG/UMG_Invenrtory"));
	if(UI_InventoryHUD.Succeeded())
	{
		InventoryWidget->SetWidgetClass(UI_InventoryHUD.Class);
		InteractionWidget->SetDrawSize(FVector2D(600.0f, 600.0f));
		InventoryWidget->SetVisibility(false);
	}

	InteractionWidget->InitWidget();
	InteractionKey = Cast<UUI_InteractionKey>(InteractionWidget->GetUserWidgetObject());
	InventoryWidget->InitWidget();
	Inventory = Cast<UUI_Inveotory>(InventoryWidget->GetUserWidgetObject());
	SpringArm->TargetArmLength = CameraDistance;
	SpringArm->SetRelativeRotation(CameraRotator);
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bDoCollisionTest = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = CameraRotationRate;
	GetCharacterMovement()->MaxWalkSpeed = WalkMaxSpeed;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("ABPlayer"));
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	////////// TODO test
	SpringArm->SetRelativeRotation(CameraRotator);
	SpringArm->TargetArmLength = CameraDistance;
	GetCharacterMovement()->MaxWalkSpeed = WalkMaxSpeed;
	////////// test

	if (DirectionToMove.SizeSquared() > 0.0f)
	{
		GetController()->SetControlRotation(FRotationMatrix::MakeFromX(DirectionToMove).Rotator());
		AddMovementInput(DirectionToMove, MoveSpeed);
	}
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// wasd 이동
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMyCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMyCharacter::LeftRight);
	
	// interaction E키
	PlayerInputComponent->BindAction(TEXT("Interaction"), EInputEvent::IE_Pressed, this, &AMyCharacter::OnInteraction);

	// inventory Tab 키
	PlayerInputComponent->BindAction(TEXT("Inventory"), EInputEvent::IE_Pressed, this, &AMyCharacter::ToggleInventoryActivation);
	
	
}

void AMyCharacter::OnInteractionStart(AABInteraction* interaction)
{
	interactionObj = interaction;
	
	UE_LOG(LogTemp, Warning, TEXT("OnInteractionStart : %s"), *interactionObj->GetName());
	UE_LOG(LogTemp, Warning, TEXT("InteractionType:%s"), *interactionObj->GetInteractionType());
	
	
	//현재 충돌중인 상초작용 오브젝트에 신호
	InteractionKey->SetInteractionKey(interactionObj->interactiontype);
	InteractionWidget->SetVisibility(true);
	
}

void AMyCharacter::OnInteractionEnd()
{
	interactionObj = NULL;
	//상호작용 UI 끄기
	InteractionWidget->SetVisibility(false);
}

void AMyCharacter::UpDown(float NewAxisValue)
{
	DirectionToMove.X = NewAxisValue;
	//UE_LOG(LogTemp, Warning, TEXT("%f"), NewAxisValue);
}

void AMyCharacter::LeftRight(float NewAxisValue)
{
	DirectionToMove.Y = NewAxisValue;
	//UE_LOG(LogTemp, Warning, TEXT("%f"), NewAxisValue);
}

void AMyCharacter::OnInteraction()
{
	// 현재 충돌중인 상호작용 오브젝트에 신호
	if (interactionObj != NULL)
	{
		interactionObj->OnInteraction();
	}
}

void AMyCharacter::ToggleInventoryActivation()
{

	if(!isInventoryActive)
	{
		//인벤토리 열기
		InventoryWidget->SetVisibility(true);
		UE_LOG(LogTemp, Warning, TEXT("OpenInventory"));
		isInventoryActive = true;
	}
	else
	{
		//인벤토리 닫기
		InventoryWidget->SetVisibility(false);
		UE_LOG(LogTemp, Warning, TEXT("CloseInventory"));
		isInventoryActive = false;
	}
	
}
