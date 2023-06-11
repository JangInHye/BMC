// Fill out your copyright notice in the Description page of Project Settings.


#include "TableInstanceSubsystem.h"
#include "UObject/ConstructorHelpers.h"

void UTableInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// 운송퀘스트 테이블 불러오기
	DeliveryQuestTable = LoadObjFromPath(TEXT("/Game/Sheets/DeliveryQuestTable"));
	DeliveryQuestConditionTable = LoadObjFromPath(TEXT("/Game/Sheets/DeliveryQuestConditionTable"));
	DeliveryQuestCompleteTable = LoadObjFromPath(TEXT("/Game/Sheets/DeliveryQuestCompleteTable"));
}

void UTableInstanceSubsystem::Deinitialize()
{
	if (DeliveryQuestTable != nullptr)
	{
		DeliveryQuestTable->EmptyTable();
	}
	if (DeliveryQuestConditionTable != nullptr)
	{
		DeliveryQuestConditionTable->EmptyTable();
	}
	if (DeliveryQuestCompleteTable != nullptr)
	{
		DeliveryQuestCompleteTable->EmptyTable();
	}
}
