// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_InteractionKey.h"

bool UUI_InteractionKey::Initialize()
{
	bool Sucess = Super::Initialize();
	if (!Sucess) return false;
	if (!ensure(Interaction_ToolTip != nullptr)) return false;
	

	return true;
}



void UUI_InteractionKey::SetInteractionKey(InteractionType type)
{
	if (type==InteractionType::DOOR)	
	{
		Interaction_ToolTip->SetText(FText::FromString(TEXT("사무실 나가기")));
		UE_LOG(LogTemp, Warning, TEXT("Interaction Type: Door"))

	};

}

