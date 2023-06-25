// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TableInstanceSubsystem.generated.h"

UENUM(BlueprintType)
enum class ETableType : uint8
{
	E_Default UMETA(DisplayName = "Quest Default"),
	E_Condition UMETA(DisplayName = "Quest Condition"),
	E_Complete UMETA(DisplayName = "Quest Complete"),
};

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

	// �� �̸� ����
	UDataTable* GetRowByName(ETableType type, FName name);
	// ID ����
	UDataTable* GetRowByID(ETableType type, int32 id);

private:
	FORCEINLINE UDataTable* LoadObjFromPath(const FName& Path)
	{
		if (Path == NAME_None) return NULL;

		return Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, *Path.ToString()));
	}

	UDataTable* GetTableByEnum(ETableType type);
};
