// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestInstanceSubsystem.h"
#include "FDeliveryQuestConditionTable.h"
using namespace std;

void UQuestInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Collection.InitializeDependency(UTableInstanceSubsystem::StaticClass());

	if (_tableSubSystem == nullptr)
	{
		_tableSubSystem = GetGameInstance()->GetSubsystem<UTableInstanceSubsystem>();
	}
	if (_playerData == nullptr)
	{
		_playerData = GetGameInstance()->GetSubsystem<UPlayerDataInstanceSubsystem>();
	}
}

void UQuestInstanceSubsystem::Deinitialize()
{
	_questVector.clear();
}

FDeliveryQuestTable UQuestInstanceSubsystem::GetQuest(int index)
{
	//if (0 <= index && index < _questVector.size()) return _questVector[index]._questData;
	if (0 <= index && index < _questVector.size()) return _questVector[index];

	FDeliveryQuestTable temp = FDeliveryQuestTable();
	temp.ID = -1;
	return temp;
}

/// <summary>
/// 퀘스트 생성
/// </summary>
void UQuestInstanceSubsystem::SetQuestList()
{
	// 기존의 데이터 제거
	_questVector.clear();

	int curDay = _playerData->GetCurDay();
	int curInvenGrade = _playerData->GetCurInvenGrade();

	list< FDeliveryQuestTable> normalDeliveryList;
	list< FDeliveryQuestTable> specialDeliveryList;

	// QuestType 1 일반택배는 3~4개 ?
	// QuestType 2 특급택배는 조건 충족하면 바로 지급
	if (_tableSubSystem == nullptr || _tableSubSystem->DeliveryQuestTable == nullptr) return;
	TArray<FName> RowNames = _tableSubSystem->DeliveryQuestTable->GetRowNames();
	for (int i = 0; i < RowNames.Num(); i++)
	{
		// 퀘스트 확인
		FDeliveryQuestTable* questTableRow = (FDeliveryQuestTable*)_tableSubSystem->GetRowByName(ETableType::E_Default, RowNames[i]);
		if (questTableRow == nullptr) continue;

		// 조건 테이블 가져오기
		FDeliveryQuestConditionTable* questConditionTableRow = (FDeliveryQuestConditionTable*)_tableSubSystem->GetRowByID(ETableType::E_Condition, questTableRow->Condition);
		if (questConditionTableRow == nullptr) continue;

		UE_LOG(LogTemp, Warning, TEXT("SetQuestList MinDay :: %d"), questConditionTableRow->MinDayCount);

		// 등장 가능한 날짜인지 체크
		if (curDay < questConditionTableRow->MinDayCount
			|| questConditionTableRow->MaxDayCount <= curDay) continue;

		// 운송가방 등급 체크
		if (curInvenGrade < questConditionTableRow->MinInventoryGrade
			|| questConditionTableRow->MaxDayCount <= curInvenGrade) continue;

		// 선행퀘스트 클리어 여부

		// ㄴ선행퀘스트 클리어 횟수 충족 체크

		// 등장비율에 따라 랜덤하게 배정
	}
}
