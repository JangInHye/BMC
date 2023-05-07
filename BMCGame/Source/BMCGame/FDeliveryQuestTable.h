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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		int32 QuestType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		int32 Start;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		int32 BlockID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		int32 MinDayCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		int32 MaxDayCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		int32 BagGrade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		int32 QuestClear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		int32 QuestClearCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		int32 CompleteType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		int32 CompleteTypeValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		int32 Rate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		int32 Reward;

};

UCLASS()
class BMCGAME_API AFDeliveryQuestTable : public AActor
{
	GENERATED_BODY()
};
