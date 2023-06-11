// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "FDeliveryQuestCompleteTable.generated.h"

USTRUCT(BlueprintType)
struct FDeliveryQuestCompleteTable : public FTableRowBase
{
	GENERATED_BODY()

public:

	// ����Ʈ ���̵�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest_Complete")
		int32 ID;

	// �Ϸ� ����
	// 1 : Ư�� ��ȣ�ۿ�, NPC�� ��ȭ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest_Complete")
		int32 CompleteType;

	// �� ���� ���� ID�� (�켱 NPC�� ������Ʈ �����ؼ� ���)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest_Complete")
		int32 CompleteTypeValue;
};

UCLASS()
class BMCGAME_API AFDeliveryQuestCompliteTable : public AActor
{
	GENERATED_BODY()
};
