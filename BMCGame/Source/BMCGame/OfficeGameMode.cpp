// Fill out your copyright notice in the Description page of Project Settings.


#include "OfficeGameMode.h"
#include "OfficeGameState.h"
#include "ABPlayerController.h"
#include "MyCharacter.h"

AOfficeGameMode::AOfficeGameMode()
{
	GameStateClass = AOfficeGameState::StaticClass();
	DefaultPawnClass = AMyCharacter::StaticClass();
	PlayerControllerClass = AABPlayerController::StaticClass();
}