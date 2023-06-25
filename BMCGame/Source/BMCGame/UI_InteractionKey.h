// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABInteraction.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "UI_InteractionKey.generated.h"

/**
 * 
 */
UCLASS()
class BMCGAME_API UUI_InteractionKey : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	    class UTextBlock* Interaction_ToolTip;
	UFUNCTION()
		void SetInteractionKey(InteractionType type);

protected:
	virtual bool Initialize();


	
};
