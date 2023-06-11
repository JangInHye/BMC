// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestInstanceSubsystem.h"
#include "GameFramework/GameModeBase.h"
#include "OfficeGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BMCGAME_API AOfficeGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	UQuestInstanceSubsystem* _questInstance;

	void StartPlay() override;
	
public:
	AOfficeGameMode();
};
