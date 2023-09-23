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
	InteractionWidget->SetupAttachment(GetCapsuleComponent());
	InventoryWidget->SetupAttachment(GetCapsuleComponent());

	// Character modeling setting
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	// interaction UI setting
	InteractionWidget->SetRelativeLocation(FVector(0.0f,0.0f,150.0f));
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
		InteractionWidget->SetDrawSize(FVector2D(140.0f, 40.0f));
		InteractionWidget->SetVisibility(false);
	}

	static ConstructorHelpers::FClassFinder<UUI_Inveotory> UI_InventoryHUD(TEXT("/Game/Dummy/UMG/UMG_Invenrtory"));
	if(UI_InventoryHUD.Succeeded())
	{
		InventoryWidget->SetWidgetClass(UI_InventoryHUD.Class);
		InventoryWidget->SetDrawSize(FVector2D(600.0f, 600.0f));
		InventoryWidget->SetVisibility(false);
	}

	InteractionWidget->InitWidget();
	InteractionKey = Cast<UUI_InteractionKey>(InteractionWidget->GetUserWidgetObject());
	InventoryWidget->InitWidget();
	Inventory = Cast<UUI_Inveotory>(InventoryWidget->GetUserWidgetObject());

	// camera setting
	SpringArm->TargetArmLength = CameraDistance;				// ī�޶� �Ÿ�
	SpringArm->SetRelativeRotation(CameraRotator);				// ī�޶� ����
	SpringArm->SetRelativeLocation(CameraLocation);				// ī�޶� ��ġ
	//SpringArm->bUsePawnControlRotation = false;			// ���ͺ� ����
	//SpringArm->bInheritPitch = false;
	//SpringArm->bInheritRoll = false;
	//SpringArm->bInheritYaw = false;
	//SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = true;
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

	// wasd �̵�
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMyCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMyCharacter::LeftRight);
	// ���콺 ȸ��
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMyCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AMyCharacter::Turn);
	
	// interaction EŰ
	PlayerInputComponent->BindAction(TEXT("Interaction"), EInputEvent::IE_Pressed, this, &AMyCharacter::OnInteraction);

	// inventory Tab Ű
	PlayerInputComponent->BindAction(TEXT("Inventory"), EInputEvent::IE_Pressed, this, &AMyCharacter::ToggleInventoryActivation);
	
	
}

void AMyCharacter::OnInteractionStart(AABInteraction* interaction)
{
	interactionObj = interaction;
	
	UE_LOG(LogTemp, Warning, TEXT("OnInteractionStart : %s"), *interactionObj->GetName());
	UE_LOG(LogTemp, Warning, TEXT("InteractionType:%s"), *interactionObj->GetInteractionType());
	
	
	//���� �浹���� �����ۿ� ������Ʈ�� ��ȣ
	InteractionKey->SetInteractionKey(interactionObj->interactiontype);
	InteractionWidget->SetVisibility(true);
	
}

void AMyCharacter::OnInteractionEnd()
{
	interactionObj = NULL;
	//��ȣ�ۿ� UI ����
	InteractionWidget->SetVisibility(false);
}

void AMyCharacter::UpDown(float NewAxisValue)
{
	//DirectionToMove.X = NewAxisValue;		//���ͺ� ����
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
	//UE_LOG(LogTemp, Warning, TEXT("%f"), NewAxisValue);
}

void AMyCharacter::LeftRight(float NewAxisValue)
{
	//DirectionToMove.Y = NewAxisValue;		//���ͺ� ����
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
	//UE_LOG(LogTemp, Warning, TEXT("%f"), NewAxisValue);
}

void AMyCharacter::LookUp(float NewAxisValue)
{
	float value = -NewAxisValue * TurnSpeed;
	if (AxisUpDownValue + value < MinAxisUpDown 
		|| MaxAxisUpDown < AxisUpDownValue + value) return;		// ���Ʒ� ī�޶� �̵��� �ּ�,�ִ� ���Ƶ���
	AxisUpDownValue += value;
	AddControllerPitchInput(value);
}

void AMyCharacter::Turn(float NewAxisValue)
{
	AddControllerYawInput(NewAxisValue * TurnSpeed);
}

void AMyCharacter::OnInteraction()
{
	// ���� �浹���� ��ȣ�ۿ� ������Ʈ�� ��ȣ
	if (interactionObj != NULL)
	{
		interactionObj->OnInteraction();
	}
}

void AMyCharacter::ToggleInventoryActivation()
{

	if(!isInventoryActive)
	{
		//�κ��丮 ����
		InventoryWidget->SetVisibility(true);
		UE_LOG(LogTemp, Warning, TEXT("OpenInventory"));
		isInventoryActive = true;
	}
	else
	{
		//�κ��丮 �ݱ�
		InventoryWidget->SetVisibility(false);
		UE_LOG(LogTemp, Warning, TEXT("CloseInventory"));
		isInventoryActive = false;
	}
	
}
