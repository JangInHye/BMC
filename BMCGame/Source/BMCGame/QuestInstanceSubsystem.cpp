// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestInstanceSubsystem.h"
#include "FDeliveryQuestConditionTable.h"

/// <summary>
/// �ʱ�ȭ
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
/// ����Ʈ �������� (�ε��� ����)
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
/// ����Ʈ ����
/// </summary>
void UQuestInstanceSubsystem::SetQuestList()
{
	// ��¥�� ���� ����Ʈ ����
	RemoveExpiryQuest();

	// Ư���ù� ����
	vector<int> specialDeliveryList = GetListup(true);
	_questVector.insert(_questVector.end(), specialDeliveryList.begin(), specialDeliveryList.end());

	// ���� ����Ʈ ����
	// �����ؾ��ϴ� ����Ʈ ����
	// ���� ����Ʈ ������ ����ϴٸ� Ư���ù踸 üũ�Ѵ�.
	if (_maxQuestCount <= _questVector.size()) return;

	// ����Ʈ�� �� ����Ʈ �߿��� �������� �ù� ä��
	vector<int> normalDeliveryList = GetListup(false);
	SelectQuest(normalDeliveryList);
}

/// <summary>
/// ������ �ù� ����Ʈ��
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
		// ����Ʈ Ȯ��
		FDeliveryQuestTable* questTableRow = (FDeliveryQuestTable*)_tableSubSystem->GetRowByName(ETableType::E_Default, RowNames[i]);
		if (questTableRow == nullptr) continue;

		// QuestType 1 �Ϲ��ù�
		// QuestType 2 Ư���ù�
		if (isSpecial ? questTableRow->QuestType == 1 : questTableRow->QuestType == 2) continue;

		// ���� ���̺� ��������
		FDeliveryQuestConditionTable* conditionTableRow = (FDeliveryQuestConditionTable*)_tableSubSystem->GetRowByID(ETableType::E_Condition, questTableRow->Condition);
		if (conditionTableRow == nullptr) continue;

		UE_LOG(LogTemp, Warning, TEXT("SetQuestList MinDay :: %d"), conditionTableRow->MinDayCount);

		// ���� ������ ��¥���� üũ
		if (curDay < conditionTableRow->MinDayCount
			|| conditionTableRow->MaxDayCount <= curDay) continue;

		// ��۰��� ��� üũ
		if (curInvenGrade < conditionTableRow->MinInventoryGrade
			|| conditionTableRow->MaxDayCount <= curInvenGrade) continue;

		// ��������Ʈ Ŭ���� ����
		int clearID = conditionTableRow->QuestClear;		// ��������Ʈ ���̵�
		if (clearID != -1)
		{
			// TODO ��������Ʈ Ŭ���� üũ �˻�
			// ��������Ʈ Ŭ���� üũ
			// ����������Ʈ Ŭ���� Ƚ�� ���� üũ
		}

		// ���������ŭ ����Ʈ�� �߰�
		for (int count = 0; count < conditionTableRow->Rate; count++)
		{
			resultList.push_back(questTableRow->ID);
		}
	}
	return resultList;
}

/// <summary>
/// ������ ����Ʈ ä��
/// </summary>
void UQuestInstanceSubsystem::SelectQuest(vector<int> listupQuest)
{
	vector<int> tempList = listupQuest;
	list<int> selectID;

	while (tempList.size() != 0
			&&_maxQuestCount <= _questVector.size())
	{
		// ����Ʈ�� �� ����Ʈ �� �ϳ� ����
		int rand = FMath::RandRange(0, tempList.size() - 1);
		int id = tempList[rand];
		_questVector.push_back(id);
		selectID.push_back(id);
		
		// ���õ� ����Ʈ�� ������ ���̵� �����ϰ� ����Ʈ �ʱ�ȭ
		tempList.clear();
		for (int lqID : listupQuest)
		{
			if(find(selectID.begin(), selectID.end(), lqID) != selectID.end()) continue;

			tempList.push_back(lqID);
		}
	}
}

/// <summary>
/// ��¥�� ���� ����Ʈ ����
/// </summary>
void UQuestInstanceSubsystem::RemoveExpiryQuest()
{
	// TODO ��¥�� ���� ����Ʈ ����
	_questVector.clear();
}
