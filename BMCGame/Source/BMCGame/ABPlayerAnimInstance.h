// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ABPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BMCGAME_API UABPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UABPlayerAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, 
		Meta=(AllowPrivateAccess = "true"))
		float CurrentCharSpeed;
};