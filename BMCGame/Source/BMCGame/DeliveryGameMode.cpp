// Fill out your copyright notice in the Description page of Project Settings.


#include "DeliveryGameMode.h"
#include "DeliveryGameState.h"
#include "ABPlayerController.h"
#include "MyCharacter.h"
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

	// 기존에 사용한 타이머가 있다면 그대로 사용
	if (GetWorldTimerManager().TimerExists(MyTimerHandle))
	{
		GetWorldTimerManager().UnPauseTimer(MyTimerHandle);
	}
	else
	{
		GetWorldTimerManager().SetTimer(MyTimerHandle, this, &ADeliveryGameMode::CheckRemainTime, 1.0f, true, 0.0f);
	}

	// 퀘스트 세팅
	UGameInstance* GameInstance = GetGameInstance();
	_questInstance = GameInstance->GetSubsystem<UQuestInstanceSubsystem>();
}

/// <summary>
/// 남은 시간 노출
/// </summary>
/// <param name="remainTime"></param>
void ADeliveryGameMode::ShowRemainTime(float remainTime)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::SanitizeFloat(remainTime));
}

/// <summary>
/// 타이머 체크
/// </summary>
void ADeliveryGameMode::CheckRemainTime()
{
	if (!GetWorldTimerManager().IsTimerActive(MyTimerHandle)) return;

	float fTimerElapsed = GetWorldTimerManager().GetTimerElapsed(MyTimerHandle);
	myTime += fTimerElapsed;

	if (myTime > timeLimit)
	{
		// 타이머 초기화 및 멈추기
		GetWorldTimerManager().PauseTimer(MyTimerHandle);
		GetWorldTimerManager().ClearTimer(MyTimerHandle);

		// 레벨 전환
		UGameplayStatics::OpenLevel(this, TEXT("OfficeLevel"));
	}

	ShowRemainTime(timeLimit - myTime);
}