// Fill out your copyright notice in the Description page of Project Settings.


#include "DeliveryGameMode.h"
#include "DeliveryGameState.h"
#include "ABPlayerController.h"
#include "MyCharacter.h"
#include "FDeliveryQuestTable.h"

#include "Kismet/GameplayStatics.h"

ADeliveryGameMode::ADeliveryGameMode()
{
	GameStateClass = ADeliveryGameState::StaticClass();
	DefaultPawnClass = AMyCharacter::StaticClass();
	PlayerControllerClass = AABPlayerController::StaticClass();
}

void ADeliveryGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void ADeliveryGameMode::StartPlay()
{
	Super::StartPlay();

	// ������ ����� Ÿ�̸Ӱ� �ִٸ� �״�� ���
	if (GetWorldTimerManager().TimerExists(MyTimerHandle))
	{
		GetWorldTimerManager().UnPauseTimer(MyTimerHandle);
	}
	else
	{
		GetWorldTimerManager().SetTimer(MyTimerHandle, this, &ADeliveryGameMode::CheckRemainTime, 1.0f, true, 0.0f);
	}

	if (TableSubSystem == nullptr)
	{
		UGameInstance* GameInstance = GetGameInstance();
		TableSubSystem = GameInstance->GetSubsystem<UTableInstanceSubsystem>();
	}

	// �о�� ��Ʈ üũ
	/*
	if (TableSubSystem != nullptr && TableSubSystem->DeliveryQuestTable != nullptr)
	{
		for (int32 i = 1; i <= 7; i++)
		{
			FDeliveryQuestTable* DeliveryQuestTableRow = TableSubSystem->DeliveryQuestTable->FindRow<FDeliveryQuestTable>(FName(*(FString::FormatAsNumber(i))), FString(""));
			UE_LOG(LogTemp, Log, TEXT("Index.%d :: QuestType(%d) Start(%d) BlockID(%d) MinDayCount(%d) MaxDayCount(%d) BagGrade(%d) QuestClear(%d) QuestClearCount(%d) CompleteType(%d) CompleteTypeValue(%d) Rate(%d) Reward(%d)"), i,
				(*DeliveryQuestTableRow).QuestType, (*DeliveryQuestTableRow).Start, (*DeliveryQuestTableRow).BlockID, (*DeliveryQuestTableRow).MinDayCount, (*DeliveryQuestTableRow).MaxDayCount, (*DeliveryQuestTableRow).BagGrade, (*DeliveryQuestTableRow).QuestClear, (*DeliveryQuestTableRow).QuestClearCount, (*DeliveryQuestTableRow).CompleteType, (*DeliveryQuestTableRow).CompleteTypeValue, (*DeliveryQuestTableRow).Rate, (*DeliveryQuestTableRow).Reward);
		}
	}*/
}

/// <summary>
/// ���� �ð� ����
/// </summary>
/// <param name="remainTime"></param>
void ADeliveryGameMode::ShowRemainTime(float remainTime)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::SanitizeFloat(remainTime));
}

/// <summary>
/// Ÿ�̸� üũ
/// </summary>
void ADeliveryGameMode::CheckRemainTime()
{
	if (!GetWorldTimerManager().IsTimerActive(MyTimerHandle)) return;

	float fTimerElapsed = GetWorldTimerManager().GetTimerElapsed(MyTimerHandle);
	myTime += fTimerElapsed;

	if (myTime > timeLimit)
	{
		// Ÿ�̸� �ʱ�ȭ �� ���߱�
		GetWorldTimerManager().PauseTimer(MyTimerHandle);
		GetWorldTimerManager().ClearTimer(MyTimerHandle);

		// ���� ��ȯ
		UGameplayStatics::OpenLevel(this, TEXT("OfficeLevel"));
	}

	ShowRemainTime(timeLimit - myTime);
}