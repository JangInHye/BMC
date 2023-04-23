// Fill out your copyright notice in the Description page of Project Settings.


#include "OfficeGameMode.h"
#include "OfficeGameState.h"

AOfficeGameMode::AOfficeGameMode()
{
	GameStateClass = AOfficeGameState::StaticClass();
}