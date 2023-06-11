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

	class UDataTable* DeliveryQuestTable;					// �������Ʈ ���̺�
	class UDataTable* DeliveryQuestConditionTable;		// �������Ʈ ���� ���̺�
	class UDataTable* DeliveryQuestCompleteTable;		// �������Ʈ �Ϸ� ���̺�
	class UDataTable* DeliveryItemTable;						// �ù� ������ ���̺�

private:
	FORCEINLINE UDataTable* LoadObjFromPath(const FName& Path)
	{
		if (Path == NAME_None) return NULL;

		return Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, *Path.ToString()));
	}
};
