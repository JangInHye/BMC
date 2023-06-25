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
/// ����Ʈ ����
/// </summary>
void UQuestInstanceSubsystem::SetQuestList()
{
	// ������ ������ ����
	_questVector.clear();

	int curDay = _playerData->GetCurDay();
	int curInvenGrade = _playerData->GetCurInvenGrade();

	list< FDeliveryQuestTable> normalDeliveryList;
	list< FDeliveryQuestTable> specialDeliveryList;

	// QuestType 1 �Ϲ��ù�� 3~4�� ?
	// QuestType 2 Ư���ù�� ���� �����ϸ� �ٷ� ����
	if (_tableSubSystem == nullptr || _tableSubSystem->DeliveryQuestTable == nullptr) return;
	TArray<FName> RowNames = _tableSubSystem->DeliveryQuestTable->GetRowNames();
	for (int i = 0; i < RowNames.Num(); i++)
	{
		// ����Ʈ Ȯ��
		FDeliveryQuestTable* questTableRow = _tableSubSystem->DeliveryQuestTable->FindRow<FDeliveryQuestTable>(RowNames[i], RowNames[i].ToString());
		if (questTableRow == nullptr) continue;

		// ���� ���̺� ��������
		// TODO ���̺��� ID�� �������� ��� �����غ���
		FDeliveryQuestConditionTable* questConditionTableRow = _tableSubSystem->DeliveryQuestConditionTable->FindRow<FDeliveryQuestConditionTable>(FName(*(FString::FormatAsNumber(questTableRow->Condition))), FString(""));
		if (questConditionTableRow == nullptr) continue;

		// ���� ������ ��¥���� üũ
		if (curDay < questConditionTableRow->MinDayCount
			|| questConditionTableRow->MaxDayCount <= curDay) continue;

		// ��۰��� ��� üũ
		if (curInvenGrade < questConditionTableRow->MinInventoryGrade
			|| questConditionTableRow->MaxDayCount <= curInvenGrade) continue;

		// ��������Ʈ Ŭ���� ����

		// ����������Ʈ Ŭ���� Ƚ�� ���� üũ

		// ��������� ���� �����ϰ� ����
	}
}