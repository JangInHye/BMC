// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Inveotory.h"
#include "Components/Button.h"

void UUI_Inveotory::NativeConstruct()
{
	Super::NativeConstruct();
	UE_LOG(LogTemp, Warning, TEXT("TEST"))
	
	Selected_Package->OnClicked.AddDynamic(this, &UUI_Inveotory::UUI_Inveotory::OnClickSelectButton);

}


void UUI_Inveotory::OnClickSelectButton()
{
	UE_LOG(LogTemp, Warning, TEXT("click"))
}

