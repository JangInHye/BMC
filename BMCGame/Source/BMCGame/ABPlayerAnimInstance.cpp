// Fill out your copyright notice in the Description page of Project Settings.


#include "ABPlayerAnimInstance.h"

UABPlayerAnimInstance::UABPlayerAnimInstance()
{
	CurrentCharSpeed = 0.0f;
}

void UABPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentCharSpeed = Pawn->GetVelocity().Size();
	}
}
