// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DeliveryGameState.generated.h"

/**
 * 
 */
UCLASS()
class BMCGAME_API ADeliveryGameState : public AGameStateBase
{
	GENERATED_BODY()

private:
	FTimerHandle MyTimerHandle;

	void BeginPlay() override;

	void ShowRemainTime(float remainTime);
	void CheckRemainTime();
	
	const float timeLimit = 5.f;
	float myTime;
public:
	ADeliveryGameState();
};
