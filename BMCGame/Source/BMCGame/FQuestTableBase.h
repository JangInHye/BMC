// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "FQuestTableBase.generated.h"

USTRUCT(BlueprintType)
struct FQuestTableBase : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuestBase")
		int32 ID;
};

UCLASS()
class BMCGAME_API AFQuestTableBase : public AActor
{
	GENERATED_BODY()
};
