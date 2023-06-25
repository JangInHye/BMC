// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "ABInteraction.h"
#include "Components/WidgetComponent.h"
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

	// 현재 충돌 중인 상호작용 오브젝트에서 호출함
	// 충돌 시작
	void OnInteractionStart(AABInteraction* interaction);
	// 충돌 끝
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
		float MoveSpeed = 0.5f;			// -1~1 사이의 값이어야 함
	UPROPERTY(EditAnywhere, Category = MyCharacter)
		float WalkMaxSpeed = 600.0f;

	//인터렉션 UI 추가
	UPROPERTY(VisibleAnywhere, Category = UI)
		class UWidgetComponent* InteractionWidget;
	


private:
	FRotator CameraRotationRate = FRotator(0.0f, 720.0f, 0.0f);
	AABInteraction* interactionObj;		// 상호작용 오브젝트가 1개라는 전제

	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);
	void OnInteraction();
};
