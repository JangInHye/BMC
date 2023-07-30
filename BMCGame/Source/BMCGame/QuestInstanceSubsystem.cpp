// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestInstanceSubsystem.h"
#include "FDeliveryQuestConditionTable.h"

/// <summary>
/// 초기화
/// </summary>
/// <param name="Collection"></param>
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

/// <summary>
/// 퀘스트 가져오기 (인덱스 기준)
/// </summary>
/// <param name="index"></param>
/// <returns></returns>
FDeliveryQuestTable UQuestInstanceSubsystem::GetQuest(int index)
{
	//if (0 <= index && index < _questVector.size()) return _questVector[index]._questData;
	if (0 <= index && index < _questVector.size()) return *(FDeliveryQuestTable*)_tableSubSystem->GetRowByID(ETableType::E_Default, _questVector[index]);

	FDeliveryQuestTable temp = FDeliveryQuestTable();
	temp.ID = -1;
	return temp;
}

/// <summary>
/// 퀘스트 생성
/// </summary>
void UQuestInstanceSubsystem::SetQuestList()
{
	// 날짜가 지난 퀘스트 제거
	RemoveExpiryQuest();

	// 특수택배 지급
	vector<int> specialDeliveryList = GetListup(true);
	_questVector.insert(_questVector.end(), specialDeliveryList.begin(), specialDeliveryList.end());

	// 현재 퀘스트 갯수
	// 지급해야하는 퀘스트 갯수
	// 현재 퀘스트 갯수가 충분하다면 특수택배만 체크한다.
	if (_maxQuestCount <= _questVector.size()) return;

	// 리스트업 된 퀘스트 중에서 실지급할 택배 채택
	vector<int> normalDeliveryList = GetListup(false);
	SelectQuest(normalDeliveryList);
}

/// <summary>
/// 지급할 택배 리스트업
/// </summary>
/// <param name="isSpecial"></param>
/// <returns></returns>
vector<int> UQuestInstanceSubsystem::GetListup(bool isSpecial)
{
	vector<int> resultList;

	int curDay = _playerData->GetCurDay();
	int curInvenGrade = _playerData->GetCurInvenGrade();

	if (_tableSubSystem == nullptr || _tableSubSystem->DeliveryQuestTable == nullptr) return resultList;
	TArray<FName> RowNames = _tableSubSystem->DeliveryQuestTable->GetRowNames();
	for (int i = 0; i < RowNames.Num(); i++)
	{
		// 퀘스트 확인
		FDeliveryQuestTable* questTableRow = (FDeliveryQuestTable*)_tableSubSystem->GetRowByName(ETableType::E_Default, RowNames[i]);
		if (questTableRow == nullptr) continue;

		// QuestType 1 일반택배
		// QuestType 2 특급택배
		if (isSpecial ? questTableRow->QuestType == 1 : questTableRow->QuestType == 2) continue;

		// 조건 테이블 가져오기
		FDeliveryQuestConditionTable* conditionTableRow = (FDeliveryQuestConditionTable*)_tableSubSystem->GetRowByID(ETableType::E_Condition, questTableRow->Condition);
		if (conditionTableRow == nullptr) continue;

		UE_LOG(LogTemp, Warning, TEXT("SetQuestList MinDay :: %d"), conditionTableRow->MinDayCount);

		// 등장 가능한 날짜인지 체크
		if (curDay < conditionTableRow->MinDayCount
			|| conditionTableRow->MaxDayCount <= curDay) continue;

		// 운송가방 등급 체크
		if (curInvenGrade < conditionTableRow->MinInventoryGrade
			|| conditionTableRow->MaxDayCount <= curInvenGrade) continue;

		// 선행퀘스트 클리어 여부
		int clearID = conditionTableRow->QuestClear;		// 선행퀘스트 아이디
		if (clearID != -1)
		{
			// TODO 선행퀘스트 클리어 체크 검사
			// 선행퀘스트 클리어 체크
			// ㄴ선행퀘스트 클리어 횟수 충족 체크
		}

		// 등장비율만큼 리스트에 추가
		for (int count = 0; count < conditionTableRow->Rate; count++)
		{
			resultList.push_back(questTableRow->ID);
		}
	}
	return resultList;
}

/// <summary>
/// 실지급 퀘스트 채택
/// </summary>
void UQuestInstanceSubsystem::SelectQuest(vector<int> listupQuest)
{
	vector<int> tempList = listupQuest;
	list<int> selectID;

	while (tempList.size() != 0
			&&_maxQuestCount <= _questVector.size())
	{
		// 리스트업 된 퀘스트 중 하나 선택
		int rand = FMath::RandRange(0, tempList.size() - 1);
		int id = tempList[rand];
		_questVector.push_back(id);
		selectID.push_back(id);
		
		// 선택된 퀘스트와 동일한 아이디 제외하고 리스트 초기화
		tempList.clear();
		for (int lqID : listupQuest)
		{
			if(find(selectID.begin(), selectID.end(), lqID) != selectID.end()) continue;

			tempList.push_back(lqID);
		}
	}
}

/// <summary>
/// 날짜가 지난 퀘스트 제거
/// </summary>
void UQuestInstanceSubsystem::RemoveExpiryQuest()
{
	// TODO 날짜가 지난 퀘스트 제거
	_questVector.clear();
}
