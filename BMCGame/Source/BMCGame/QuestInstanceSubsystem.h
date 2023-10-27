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
	FDeliveryQuestTable GetQuest(int index);		// 퀘스트 가져오기
	void SetQuestList();									// 퀘스트 생성
	int IsQuestExist(int questID);					// 퀘스트가 존재하는 지 체크 (인덱스를 리턴한다.)
	void ClearQuest(int questID);						// 퀘스트 클리어

private:
	UTableInstanceSubsystem* _tableSubSystem;
	UPlayerDataInstanceSubsystem* _playerData;	// 플레이어 데이터
	vector<int> _questVector;							// 현재 진행중인 퀘스트
	int _maxQuestCount;								// 최대 퀘스트 갯수

	void GetListup(bool isSpecial, vector<int>& resultList);
	void SelectQuest(vector<int> listupQuest);
	void RemoveExpiryQuest();
};
