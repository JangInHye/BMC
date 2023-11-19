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

	// player char Anim
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT("/Game/Dummy/Characters/Player/Namo.Namo"));
	if (SK_CARDBOARD.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_CARDBOARD.Object);
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> NAMO_ANIM(TEXT("/Game/Dummy/Characters/Player/Namo_Anim_BP"));
	if (NAMO_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(NAMO_ANIM.Class);
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
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = true;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
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

	SpringArm->SetRelativeRotation(CameraRotator);
	SpringArm->TargetArmLength = CameraDistance;
	GetCharacterMovement()->MaxWalkSpeed = WalkMaxSpeed;

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
	PlayerInputComponent->BindAction(TEXT("Camera_Rotate"), EInputEvent::IE_Pressed, this, &AMyCharacter::OnCameraRotate);
	PlayerInputComponent->BindAction(TEXT("Camera_Rotate"), EInputEvent::IE_Released, this, &AMyCharacter::OnCameraRotateEnd);
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

/// <summary>
/// ����Ʈ Ŭ����
/// </summary>
/// <param name="questID"></param>
void AMyCharacter::QuestClear(int questID)
{
	// ����Ʈ ����
	if (_questInstance == nullptr)
	{
		UGameInstance* GameInstance = GetGameInstance();
		_questInstance = GameInstance->GetSubsystem<UQuestInstanceSubsystem>();
	}

	_questInstance->ClearQuest(questID);
}

/// <summary>
/// ĳ���� �յ� �̵�
/// </summary>
/// <param name="NewAxisValue"></param>
void AMyCharacter::UpDown(float NewAxisValue)
{
	if (MyState != EStateType::E_Move) return;

	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue);
	//UE_LOG(LogTemp, Warning, TEXT("%f"), NewAxisValue);
}

/// <summary>
/// ĳ���� �¿� �̵�
/// </summary>
/// <param name="NewAxisValue"></param>
void AMyCharacter::LeftRight(float NewAxisValue)
{
	if (MyState != EStateType::E_Move) return;

	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue);
	//UE_LOG(LogTemp, Warning, TEXT("%f"), NewAxisValue);
}

/// <summary>
/// ī�޶� ���Ʒ�
/// </summary>
/// <param name="NewAxisValue"></param>
void AMyCharacter::LookUp(float NewAxisValue)
{
	if (IsRotateState == false || MyState != EStateType::E_Move) return;

	float value = -NewAxisValue * TurnSpeed;
	if (AxisUpDownValue + value < MinAxisUpDown 
		|| MaxAxisUpDown < AxisUpDownValue + value) return;		// ���Ʒ� ī�޶� �̵��� �ּ�,�ִ� ���Ƶ���
	AxisUpDownValue += value;
	AddControllerPitchInput(value);
}

/// <summary>
/// ī�޶� ȸ��
/// </summary>
/// <param name="NewAxisValue"></param>
void AMyCharacter::Turn(float NewAxisValue)
{
	if (IsRotateState == false || MyState != EStateType::E_Move) return;

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

void AMyCharacter::OnCameraRotate()
{
	IsRotateState = true;
}

void AMyCharacter::OnCameraRotateEnd()
{
	IsRotateState = false;
}

void AMyCharacter::ToggleInventoryActivation()
{

	if(!isInventoryActive)
	{
		//�κ��丮 ����
		InventoryWidget->SetVisibility(true);
		UE_LOG(LogTemp, Warning, TEXT("OpenInventory"));
		isInventoryActive = true;

		ChangeState(EStateType::E_Inventory);
	}
	else
	{
		//�κ��丮 �ݱ�
		InventoryWidget->SetVisibility(false);
		UE_LOG(LogTemp, Warning, TEXT("CloseInventory"));
		isInventoryActive = false;
		ChangeState(EStateType::E_Move);
	}
	
}

/// <summary>
/// ���� ����
/// </summary>
/// <param name="curType"></param>
void AMyCharacter::ChangeState(EStateType curType)
{
	MyState = curType;
}
