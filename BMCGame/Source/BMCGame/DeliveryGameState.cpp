// Fill out your copyright notice in the Description page of Project Settings.


#include "DeliveryGameState.h"
#include "Kismet/GameplayStatics.h"

ADeliveryGameState::ADeliveryGameState() 
{
	//GetWorldTimerManager().SetTimer(MyTimerHandle, this, &ADeliveryGameState::CheckRemainTime, 1.0f, true, 10.0f);

	UGameplayStatics::OpenLevel(this, TEXT("OfficeLevel"));

}

void ADeliveryGameState::ShowRemainTime(float remainTime)
{
	UE_LOG(LogTemp, Log, TEXT("%.3f"), remainTime);
}

void ADeliveryGameState::CheckRemainTime() 
{
	if (!GetWorldTimerManager().IsTimerActive(MyTimerHandle)) return;

	float fTimerElapsed = GetWorldTimerManager().GetTimerElapsed(MyTimerHandle);

	if (fTimerElapsed <= 0)
	{
		GetWorldTimerManager().ClearTimer(MyTimerHandle);

		UGameplayStatics::OpenLevel(this, TEXT("OfficeLevel"));
	}

	ShowRemainTime(fTimerElapsed);
}