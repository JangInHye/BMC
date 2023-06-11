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

	// 퀘스트 아이디
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest_Condition")
		int32 ID;

	// 등장 가능 최소 날짜
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest_Condition")
		int32 MinDayCount;

	// 등장 가능 최대 날짜
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest_Condition")
		int32 MaxDayCount;

	// 현재 유저의 가방 등급 체크
	// 등급의 숫자가 해당 컬럼 값과 같거나 높을 시 퀘스트 지급 가능
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest_Condition")
		int32 MinInventoryGrade;

	// 현재 유저의 가방 등급 체크
	// Grade의 숫자가 해당 컬럼보다 높을 시 지급 불가
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest_Condition")
		int32 MaxInventoryGrade;

	// 특정 퀘스트 클리어 여부 (Quest ID 입력)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest_Condition")
		int32 QuestClear;

	// 위 퀘스트 클리어 횟수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest_Condition")
		int32 QuestClearCount;

	// 등장 비율
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest_Condition")
		int32 Rate;
};

UCLASS()
class BMCGAME_API AFDeliveryQuestConditionTable : public AActor
{
	GENERATED_BODY()
	
};
