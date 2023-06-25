// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "ABInteraction.h"
#include "Components/WidgetComponent.h"
#include "UI_InteractionKey.h"
#include "MyCharacter.generated.h"

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
	// �浹 ��
	void OnInteractionEnd();

	UPROPERTY(VisibleAnywhere, Category = Camera)
		USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = Camera)
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = Camera)
		FRotator CameraRotator = FRotator(-55.0f, 0.0f, 0.0f);
	UPROPERTY(EditAnywhere, Category = Camera)
		float CameraDistance = 800.0f;
	UPROPERTY(EditAnywhere, Category = MyCharacter)
		float MoveSpeed = 0.5f;			// -1~1 ������ ���̾�� ��
	UPROPERTY(EditAnywhere, Category = MyCharacter)
		float WalkMaxSpeed = 600.0f;

	//���ͷ��� UI �߰�
	UPROPERTY(VisibleAnywhere, Category = UI)
		class UWidgetComponent* InteractionWidget;
	UPROPERTY(VisibleAnywhere, Category = UI)
		class UUI_InteractionKey* InteractionKey;
	


private:
	FRotator CameraRotationRate = FRotator(0.0f, 720.0f, 0.0f);
	AABInteraction* interactionObj;		// ��ȣ�ۿ� ������Ʈ�� 1����� ����

	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);
	void OnInteraction();
};
