// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LevelDataInstanceSubsystem.generated.h"

/// <summary>
/// 레벨 이름
/// </summary>
enum class ELevelType : uint8
{
	E_Default UMETA(DisplayName = "LevelType Default"),
	E_Office UMETA(DisplayName = "LevelType Office"),
	E_Delivery UMETA(DisplayName = "LevelType Delivery"),
};

/**
 * 
 */
UCLASS()
class BMCGAME_API ULevelDataInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	ELevelType GetCurState() { return MyState; }
	void SetCurState(ELevelType state) { MyState = state; }
	
private:
	ELevelType MyState = ELevelType::E_Default;
};
