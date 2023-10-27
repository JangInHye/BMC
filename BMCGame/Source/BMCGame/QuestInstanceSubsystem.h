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
 * ����Ʈ �����ؼ� ���⼭ �� ó���� ��
 */
UCLASS()
class BMCGAME_API UQuestInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	FDeliveryQuestTable GetQuest(int index);		// ����Ʈ ��������
	void SetQuestList();									// ����Ʈ ����
	int IsQuestExist(int questID);					// ����Ʈ�� �����ϴ� �� üũ (�ε����� �����Ѵ�.)
	void ClearQuest(int questID);						// ����Ʈ Ŭ����

private:
	UTableInstanceSubsystem* _tableSubSystem;
	UPlayerDataInstanceSubsystem* _playerData;	// �÷��̾� ������
	vector<int> _questVector;							// ���� �������� ����Ʈ
	int _maxQuestCount;								// �ִ� ����Ʈ ����

	void GetListup(bool isSpecial, vector<int>& resultList);
	void SelectQuest(vector<int> listupQuest);
	void RemoveExpiryQuest();
};
