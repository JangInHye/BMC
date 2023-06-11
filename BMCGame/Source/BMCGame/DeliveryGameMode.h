// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestInstanceSubsystem.h"
#include "GameFramework/GameModeBase.h"
#include "DeliveryGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BMCGAME_API ADeliveryGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADeliveryGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;

private:
	FTimerHandle MyTimerHandle;
	UQuestInstanceSubsystem* _questInstance;

	void StartPlay() override;

	void ShowRemainTime(float remainTime);
	void CheckRemainTime();

	const float timeLimit = 1000.f;
	float myTime;
};
