// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "FDeliveryQuestConditionTable.generated.h"

USTRUCT(BlueprintType)
struct FDeliveryQuestConditionTable : public FTableRowBase
{
	GENERATED_BODY()

public:

	// ����Ʈ ���̵�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest_Condition")
		int32 ID;

	// ���� ���� �ּ� ��¥
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest_Condition")
		int32 MinDayCount;

	// ���� ���� �ִ� ��¥
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest_Condition")
		int32 MaxDayCount;

	// ���� ������ ���� ��� üũ
	// ����� ���ڰ� �ش� �÷� ���� ���ų� ���� �� ����Ʈ ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest_Condition")
		int32 MinInventoryGrade;

	// ���� ������ ���� ��� üũ
	// Grade�� ���ڰ� �ش� �÷����� ���� �� ���� �Ұ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest_Condition")
		int32 MaxInventoryGrade;

	// Ư�� ����Ʈ Ŭ���� ���� (Quest ID �Է�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest_Condition")
		int32 QuestClear;

	// �� ����Ʈ Ŭ���� Ƚ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest_Condition")
		int32 QuestClearCount;

	// ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest_Condition")
		int32 Rate;
};

UCLASS()
class BMCGAME_API AFDeliveryQuestConditionTable : public AActor
{
	GENERATED_BODY()
	
};
