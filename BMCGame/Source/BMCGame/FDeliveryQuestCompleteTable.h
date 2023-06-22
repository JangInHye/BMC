// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "FQuestTableBase.h"
#include "FDeliveryQuestCompleteTable.generated.h"

USTRUCT(BlueprintType)
struct FDeliveryQuestCompleteTable : public FQuestTableBase
{
	GENERATED_BODY()

public:

	// 퀘스트 아이디
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest_Complete")
	//	int32 ID;

	// 완료 조건
	// 1 : 특정 상호작용, NPC와 대화
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest_Complete")
		int32 CompleteType;

	// 위 값에 따른 ID값 (우선 NPC와 오브젝트 통일해서 사용)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest_Complete")
		int32 CompleteTypeValue;
};

UCLASS()
class BMCGAME_API AFDeliveryQuestCompliteTable : public AActor
{
	GENERATED_BODY()
};
