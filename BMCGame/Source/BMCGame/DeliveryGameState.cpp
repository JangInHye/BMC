// Fill out your copyright notice in the Description page of Project Settings.


#include "DeliveryGameState.h"

#include "Kismet/GameplayStatics.h"

ADeliveryGameState::ADeliveryGameState() 
{
}

void ADeliveryGameState::BeginPlay() 
{
	// ������ ����� Ÿ�̸Ӱ� �ִٸ� �״�� ���
	if (GetWorldTimerManager().TimerExists(MyTimerHandle))
	{
		GetWorldTimerManager().UnPauseTimer(MyTimerHandle);
	}
	else 
	{
		GetWorldTimerManager().SetTimer(MyTimerHandle, this, &ADeliveryGameState::CheckRemainTime, 1.0f, true, 0.0f);
	}
}

/// <summary>
/// ���� �ð� ����
/// </summary>
/// <param name="remainTime"></param>
void ADeliveryGameState::ShowRemainTime(float remainTime)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::SanitizeFloat(remainTime));
}

/// <summary>
/// Ÿ�̸� üũ
/// </summary>
void ADeliveryGameState::CheckRemainTime() 
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