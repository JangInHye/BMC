// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TableInstanceSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class BMCGAME_API UTableInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	class UDataTable* DeliveryQuestTable;					// 운송퀘스트 테이블
	class UDataTable* DeliveryQuestConditionTable;		// 운송퀘스트 조건 테이블
	class UDataTable* DeliveryQuestCompleteTable;		// 운송퀘스트 완료 테이블
	class UDataTable* DeliveryItemTable;						// 택배 아이템 테이블

private:
	FORCEINLINE UDataTable* LoadObjFromPath(const FName& Path)
	{
		if (Path == NAME_None) return NULL;

		return Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, *Path.ToString()));
	}
};
