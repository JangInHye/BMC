// Fill out your copyright notice in the Description page of Project Settings.


#include "TableInstanceSubsystem.h"
#include "UObject/ConstructorHelpers.h"

void UTableInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	// 운송퀘스트 테이블 불러오기
	DeliveryQuestTable = LoadObjFromPath(TEXT("/Game/Sheets/DeliveryQuestTable"));
	//static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("/Game/Sheets/DeliveryQuestTable"));
	/*if (DataTable.Succeeded())
	{
		DeliveryQuestTable = DataTable.Object;
	}*/
}

void UTableInstanceSubsystem::Deinitialize()
{
	DeliveryQuestTable->EmptyTable();
}
