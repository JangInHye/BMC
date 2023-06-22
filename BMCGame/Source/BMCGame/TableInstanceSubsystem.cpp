// Fill out your copyright notice in the Description page of Project Settings.


#include "TableInstanceSubsystem.h"
#include "UObject/ConstructorHelpers.h"
#include "FDeliveryQuestTable.h"
#include "FDeliveryQuestConditionTable.h"
#include "FDeliveryQuestCompleteTable.h"

void UTableInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Collection.InitializeDependency(UTableInstanceSubsystem::StaticClass());

	// 운송퀘스트 테이블 불러오기
	DeliveryQuestTable = LoadObjFromPath(TEXT("/Game/Sheets/DeliveryQuestTable"));
	DeliveryQuestConditionTable = LoadObjFromPath(TEXT("/Game/Sheets/DeliveryQuestConditionTable"));
	DeliveryQuestCompleteTable = LoadObjFromPath(TEXT("/Game/Sheets/DeliveryQuestCompleteTable"));
}

void UTableInstanceSubsystem::Deinitialize()
{
	DeliveryQuestTable = nullptr;
	DeliveryQuestConditionTable = nullptr;
	DeliveryQuestCompleteTable = nullptr;
}

UDataTable* UTableInstanceSubsystem::GetRowByName(ETableType type, FName name)
{
	UE_LOG(LogTemp, Warning, TEXT("GetRowByName :: %d"), *name.ToString());

	UDataTable* table = GetTableByEnum(type);

	switch (type)
	{
	case ETableType::E_Default:
		return (UDataTable*)table->FindRow<FDeliveryQuestTable>(name, name.ToString());
	case ETableType::E_Condition:
		return (UDataTable*)table->FindRow<FDeliveryQuestConditionTable>(name, name.ToString());
	case ETableType::E_Complete:
		return (UDataTable*)table->FindRow<FDeliveryQuestCompleteTable>(name, name.ToString());
	default:
		break;
	}

	return nullptr;
}

UDataTable* UTableInstanceSubsystem::GetRowByID(ETableType type, int32 id)
{
	UDataTable* table = GetTableByEnum(type);

	TArray<FName> RowNames = table->GetRowNames();
	for (int i = 0; i < RowNames.Num(); i++)
	{
		FQuestTableBase* questTableRow = (FQuestTableBase*)GetRowByName(type, RowNames[i]);
		if (questTableRow == nullptr) continue;
		if (questTableRow->ID == id) return (UDataTable*)questTableRow;
	}
	return nullptr;
}

UDataTable* UTableInstanceSubsystem::GetTableByEnum(ETableType type)
{
	switch (type)
	{
	case ETableType::E_Default:		return DeliveryQuestTable;
	case ETableType::E_Condition:		return DeliveryQuestConditionTable;
	case ETableType::E_Complete:		return DeliveryQuestCompleteTable;
	default: break;
	}
	return nullptr;
}
