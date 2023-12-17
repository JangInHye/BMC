// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "UI_Inveotory.generated.h"

/**
 * 
 */
UCLASS()
class BMCGAME_API UUI_Inveotory : public UUserWidget
{
	GENERATED_BODY()
public:
		UPROPERTY(meta = (BindWidget))
		class UButton* Selected_Package= nullptr;
		UFUNCTION()
		void OnClickSelectButton();
	
protected:

	virtual void NativeConstruct() override;
	
};
