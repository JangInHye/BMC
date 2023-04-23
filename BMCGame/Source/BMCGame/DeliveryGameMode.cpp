// Fill out your copyright notice in the Description page of Project Settings.


#include "DeliveryGameMode.h"
#include "DeliveryGameState.h"


ADeliveryGameMode::ADeliveryGameMode()
{
	GameStateClass = ADeliveryGameState::StaticClass();
}