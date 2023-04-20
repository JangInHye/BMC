// Copyright Epic Games, Inc. All Rights Reserved.


#include "BMCGameGameModeBase.h"
#include "DeliveryGameState.h"

ABMCGameGameModeBase::ABMCGameGameModeBase()
{
	GameStateClass = ADeliveryGameState::StaticClass();
}