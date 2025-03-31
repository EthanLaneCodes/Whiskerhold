// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnimInstance.h"
#include "ParkourGameBase.h"
#include "ParkourCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	ParkourCharacter = Cast<AParkourCharacter>(TryGetPawnOwner());
}

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!ParkourCharacter)
	{
		ParkourCharacter = Cast<AParkourCharacter>(TryGetPawnOwner());
	}

	if (!ParkourCharacter) return;
	 
	bIsJumping = ParkourCharacter->bIsJumping;
	bIsCrouching = ParkourCharacter->bIsCrouching;
	bIsAttacking = ParkourCharacter->bIsAttacking;
	UpdateSpeed(ParkourCharacter->MoveSpeed);

}

void UCharacterAnimInstance::UpdateSpeed(float NewSpeed)
{
	Speed = NewSpeed;
}


