// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
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

	UPROPERTY(VisibleAnywhere, Category = Camera)
		USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = Camera)
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = Camera)
		FRotator CameraRotator = FRotator(-45.0f, 0.0f, 0.0f);
	UPROPERTY(EditAnywhere, Category = MyCharacter)
		float MoveSpeed = 1.0f;

private:
	FRotator CameraRotationRate = FRotator(0.0f, 720.0f, 0.0f);

	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);
};
