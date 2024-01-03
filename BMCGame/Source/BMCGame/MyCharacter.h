// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestInstanceSubsystem.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InteractionItem/ABInteraction.h"
#include "Components/WidgetComponent.h"
#include "UI/UI_InteractionKey.h"
#include "UI_Inveotory.h"
#include "LevelDataInstanceSubsystem.h"
#include "MyCharacter.generated.h"

/// <summary>
/// ���� ����
/// </summary>
enum class EStateType : uint8
{
	E_Move UMETA(DisplayName = "StateType Ingame"),
	E_Inventory UMETA(DisplayName = "StateType Inventory"),
};

UCLASS()
class BMCGAME_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector DirectionToMove = FVector::ZeroVector;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ���� �浹 ���� ��ȣ�ۿ� ������Ʈ���� ȣ����
	// �浹 ����
	void OnInteractionStart(AABInteraction* interaction);
	//�浹 ��
	void OnInteractionEnd();

	// ����Ʈ Ŭ�����ϱ�
	void QuestClear(int questID);

	UPROPERTY(VisibleAnywhere, Category = Camera)
		USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = Camera)
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = MyCharacter)
		FVector CameraLocation = FVector(0.0f, 0.0f, 90.0f);		// �յ� / �¿� / ���Ʒ�
	UPROPERTY(EditAnywhere, Category = Camera)
		FRotator CameraRotator = FRotator(-55.0f, 0.0f, 0.0f);
	UPROPERTY(EditAnywhere, Category = Camera)
		float CameraDistance = 700.0f;
	UPROPERTY(EditAnywhere, Category = MyCharacter)
		float MoveSpeed = 0.5f;			// -1~1 ������ ���̿��� ��
	UPROPERTY(EditAnywhere, Category = MyCharacter)
		float WalkMaxSpeed = 350.0f;
	UPROPERTY(EditAnywhere, Category = MyCharacter)
		float TurnSpeed = 0.5f;
	UPROPERTY(EditAnywhere, Category = MyCharacter)
		float MaxAxisUpDown = 25.0f;
	UPROPERTY(EditAnywhere, Category = MyCharacter)
		float MinAxisUpDown = -15.0f;

	//���ͷ��� UI �߰�
	UPROPERTY(VisibleAnywhere, Category = UI_interaction)
		class UWidgetComponent* InteractionWidget;
	UPROPERTY(VisibleAnywhere, Category = UI_interaction)
		class UUI_InteractionKey* InteractionKey;

	//�κ��丮 â ����Ȯ�� (Open/Close)
	UPROPERTY(VisibleAnywhere, Category = Inventory)
		bool isInventoryActive = false;
	//�κ��丮 UI �߰�
	UPROPERTY(VisibleAnywhere, Category = Inventory)
		class UWidgetComponent* InventoryWidget;
	UPROPERTY(VisibleAnywhere, Category = Inventory)
		class UUI_Inveotory* Inventory;


	


private:
	FRotator CameraRotationRate = FRotator(0.0f, 720.0f, 0.0f);
	AABInteraction* interactionObj;		// ��ȣ�ۿ� ������Ʈ�� 1����� ����
	UQuestInstanceSubsystem* _questInstance;
	float AxisUpDownValue = 0.0f;
	bool IsRotateState = false;				// ���콺 ��Ŭ�� üũ

	EStateType MyState = EStateType::E_Move;
	ULevelDataInstanceSubsystem* _levelData;	// ���� ������

	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);
	void OnInteraction();
	void OnCameraRotate();
	void OnCameraRotateEnd();
	void ToggleInventoryActivation();
	
	void ChangeState(EStateType curType);
};
