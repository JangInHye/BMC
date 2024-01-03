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
/// 조작 상태
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

	// 현재 충돌 중인 상호작용 오브젝트에서 호출함
	// 충돌 시작
	void OnInteractionStart(AABInteraction* interaction);
	//충돌 끝
	void OnInteractionEnd();

	// 퀘스트 클리어하기
	void QuestClear(int questID);

	UPROPERTY(VisibleAnywhere, Category = Camera)
		USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = Camera)
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = MyCharacter)
		FVector CameraLocation = FVector(0.0f, 0.0f, 90.0f);		// 앞뒤 / 좌우 / 위아래
	UPROPERTY(EditAnywhere, Category = Camera)
		FRotator CameraRotator = FRotator(-55.0f, 0.0f, 0.0f);
	UPROPERTY(EditAnywhere, Category = Camera)
		float CameraDistance = 700.0f;
	UPROPERTY(EditAnywhere, Category = MyCharacter)
		float MoveSpeed = 0.5f;			// -1~1 사이의 값이여야 함
	UPROPERTY(EditAnywhere, Category = MyCharacter)
		float WalkMaxSpeed = 350.0f;
	UPROPERTY(EditAnywhere, Category = MyCharacter)
		float TurnSpeed = 0.5f;
	UPROPERTY(EditAnywhere, Category = MyCharacter)
		float MaxAxisUpDown = 25.0f;
	UPROPERTY(EditAnywhere, Category = MyCharacter)
		float MinAxisUpDown = -15.0f;

	//인터렉션 UI 추가
	UPROPERTY(VisibleAnywhere, Category = UI_interaction)
		class UWidgetComponent* InteractionWidget;
	UPROPERTY(VisibleAnywhere, Category = UI_interaction)
		class UUI_InteractionKey* InteractionKey;

	//인벤토리 창 상태확인 (Open/Close)
	UPROPERTY(VisibleAnywhere, Category = Inventory)
		bool isInventoryActive = false;
	//인벤토리 UI 추가
	UPROPERTY(VisibleAnywhere, Category = Inventory)
		class UWidgetComponent* InventoryWidget;
	UPROPERTY(VisibleAnywhere, Category = Inventory)
		class UUI_Inveotory* Inventory;


	


private:
	FRotator CameraRotationRate = FRotator(0.0f, 720.0f, 0.0f);
	AABInteraction* interactionObj;		// 상호작용 오브젝트가 1개라는 전제
	UQuestInstanceSubsystem* _questInstance;
	float AxisUpDownValue = 0.0f;
	bool IsRotateState = false;				// 마우스 우클릭 체크

	EStateType MyState = EStateType::E_Move;
	ULevelDataInstanceSubsystem* _levelData;	// 레벨 데이터

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
