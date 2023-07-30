// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include "TableInstanceSubsystem.h"
#include "PlayerDataInstanceSubsystem.h"
#include "FDeliveryQuestTable.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QuestInstanceSubsystem.generated.h"
using namespace std;
//
//struct QuestDataStruct
//{
//public:
//	FDeliveryQuestTable _questData;
//	bool _isClear;
//};

/**
 * 퀘스트 관련해서 여기서 다 처리할 것
 */
UCLASS()
class BMCGAME_API UQuestInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	FDeliveryQuestTable GetQuest(int index);
	void SetQuestList();

private:
	UTableInstanceSubsystem* _tableSubSystem;
	UPlayerDataInstanceSubsystem* _playerData;
	vector<int> _questVector;
	int _maxQuestCount;

	vector<int> GetListup(bool isSpecial);
	void SelectQuest(vector<int> listupQuest);
	void RemoveExpiryQuest();
};
