// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include "TableInstanceSubsystem.h"
#include "PlayerDataInstanceSubsystem.h"
#include "FDeliveryQuestTable.h"
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
 * ����Ʈ �����ؼ� ���⼭ �� ó���� ��
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
	std::vector<FDeliveryQuestTable> _questVector;
};