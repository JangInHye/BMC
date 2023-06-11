// Fill out your copyright notice in the Description page of Project Settings.


#include "OfficeGameMode.h"
#include "OfficeGameState.h"
#include "ABPlayerController.h"
#include "MyCharacter.h"

void AOfficeGameMode::StartPlay()
{
	// Äù½ºÆ® ¼¼ÆÃ
	UGameInstance* GameInstance = GetGameInstance();
	_questInstance = GameInstance->GetSubsystem<UQuestInstanceSubsystem>();
	_questInstance->SetQuestList();
}

AOfficeGameMode::AOfficeGameMode()
{
	GameStateClass = AOfficeGameState::StaticClass();
	DefaultPawnClass = AMyCharacter::StaticClass();
	PlayerControllerClass = AABPlayerController::StaticClass();
}
