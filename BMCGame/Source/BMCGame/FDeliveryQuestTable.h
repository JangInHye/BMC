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

	// 퀘스트 아이디
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		int32 ID;

	// 퀘스트 타입
	// 1 : 일반 택배
	// 2 : 특급 택배 (1회성 지급)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		int32 QuestType;

	// 해당 퀘스트에 지급할 택배 ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		int32 BlockID;

	// 퀘스트 지급 조건
	// QuestConditionTable ID값 참조
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		int32 Condition;

	// 퀘스트 완료 조건
	// QuestCompleteTable ID값 참조
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		int32 Complete;

	// 보관 가능 날짜
	// 최초 보관일부터 해당 날짜가 지나면 삭제
	// -1일 경우 보관기한 무제한
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		int32 Expirydate;

	// 퀘스트 명 (String Table 사용)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		FText QuestName;

	// 퀘스트 주소 (String Table 사용)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		FText QuestAddress;

	// 퀘스트 성공 시 출력 다이얼로그 (Dialogue_Table ID 참조)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		int32 CompleteDialogue;

	// 퀘스트 실패 시 출력 다이얼로그 (Dialogue_Table ID 참조)
	// 오브젝트 및 NPC와 상호작용 시 나오는 텍스트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		int32 FailDialogue;

	// Reward ID 값
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryQuest")
		int32 Reward;
};

UCLASS()
class BMCGAME_API AFDeliveryQuestTable : public AActor
{
	GENERATED_BODY()
};
