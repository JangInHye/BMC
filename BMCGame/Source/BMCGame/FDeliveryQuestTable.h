// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "FDeliveryQuestTable.generated.h"

USTRUCT(BlueprintType)
struct FDeliveryQuestTable : public FTableRowBase
{
	GENERATED_BODY()

public:

	// ����Ʈ ���̵�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		int32 ID;

	// ����Ʈ Ÿ��
	// 1 : �Ϲ� �ù�
	// 2 : Ư�� �ù� (1ȸ�� ����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		int32 QuestType;

	// �ش� ����Ʈ�� ������ �ù� ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		int32 BlockID;

	// ����Ʈ ���� ����
	// QuestConditionTable ID�� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		int32 Condition;

	// ����Ʈ �Ϸ� ����
	// QuestCompleteTable ID�� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		int32 Complete;

	// ���� ���� ��¥
	// ���� �����Ϻ��� �ش� ��¥�� ������ ����
	// -1�� ��� �������� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		int32 Expirydate;

	// ����Ʈ �� (String Table ���)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		FText QuestName;

	// ����Ʈ �ּ� (String Table ���)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		FText QuestAddress;

	// ����Ʈ ���� �� ��� ���̾�α� (Dialogue_Table ID ����)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		int32 CompleteDialogue;

	// ����Ʈ ���� �� ��� ���̾�α� (Dialogue_Table ID ����)
	// ������Ʈ �� NPC�� ��ȣ�ۿ� �� ������ �ؽ�Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		int32 FailDialogue;

	// Reward ID ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		int32 Reward;
};

UCLASS()
class BMCGAME_API AFDeliveryQuestTable : public AActor
{
	GENERATED_BODY()
};
