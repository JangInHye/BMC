// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FDeliveryQuestTable.h"
#include <vector>
#include "PlayerDataInstanceSubsystem.h"
#include "TableInstanceSubsystem.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QuestInstanceSubsystem.generated.h"
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
	const int MAX_QUEST_COUNT = 3;		// TODO 추후 테이블에 있는 데이터를 가져와 사용할 것

	UTableInstanceSubsystem* _tableSubSystem;
	UPlayerDataInstanceSubsystem* _playerData;
	std::vector<FDeliveryQuestTable> _questVector;
};
