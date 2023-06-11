// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestInstanceSubsystem.h"
#include "FDeliveryQuestTable.h"
#include "FDeliveryQuestConditionTable.h"
using namespace std;

void UQuestInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if (_tableSubSystem == nullptr)
	{
		UGameInstance* GameInstance = GetGameInstance();
		_tableSubSystem = GameInstance->GetSubsystem<UTableInstanceSubsystem>();
	}
	if (_playerData == nullptr)
	{
		UGameInstance* GameInstance = GetGameInstance();
		_playerData = GameInstance->GetSubsystem<UPlayerDataInstanceSubsystem>();
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
	int curInventoryGrade = _playerData->GetCurInvenGrade();

	list< FDeliveryQuestTable> normalDeliveryList;
	list< FDeliveryQuestTable> specialDeliveryList;

	// QuestType 1 �Ϲ��ù�� 3~4�� ?
	// QuestType 2 Ư���ù�� ���� �����ϸ� �ٷ� ����
	for (int i = 0; i < _tableSubSystem->DeliveryQuestTable->GetRowMap().Num(); i++)
	{
		// ����Ʈ Ȯ��
		FDeliveryQuestTable* questTableRow = _tableSubSystem->DeliveryQuestTable->FindRow<FDeliveryQuestTable>(FName(*(FString::FormatAsNumber(i))), FString(""));

		// ���� ���̺� ��������
		FDeliveryQuestConditionTable* questConditionTableRow = _tableSubSystem->DeliveryQuestConditionTable->FindRow<FDeliveryQuestConditionTable>(FName(*(FString::FormatAsNumber(questTableRow->Condition))), FString(""));

		// ���� ������ ��¥���� üũ

		// ��۰��� ��� üũ

		// ��������Ʈ Ŭ���� ����

		// ����������Ʈ Ŭ���� Ƚ�� ���� üũ

		// ��������� ���� �����ϰ� ����
	}
}
