// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FDeliveryQuestTable.h"
#include <vector>
#include "Subsystems/GameInstanceSubsystem.h"
#include "PlayerDataInstanceSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class BMCGAME_API UPlayerDataInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	int GetCurDay() { return _curDay; }
	void SetCurDay(int day) { _curDay = day; }
	int GetCurInvenGrade() { return _curInventoryGrade; }
	void SetCurInvenGrade(int grade) { _curInventoryGrade = grade; }

private:
	int _curDay = 0;
	int _curInventoryGrade = 0;
	int _myCoin = 0;
	std::vector<FDeliveryQuestTable> _storageVector;
};
