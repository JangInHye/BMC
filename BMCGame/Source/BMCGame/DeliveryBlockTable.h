// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "DeliveryBlockTable.generated.h"

USTRUCT(BlueprintType)
struct FDelivery_BlockTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryBlock")
	    int32 ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryBlock")
		int32 Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeliveryBlock")
		FString Size;

};


UCLASS()
class BMCGAME_API ADeliveryBlockTable : public AActor
{
	GENERATED_BODY()

};
