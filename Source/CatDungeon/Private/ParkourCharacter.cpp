// Fill out your copyright notice in the Description page of Project Settings.


#include "ParkourCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "ParkourPlayerState.h"
#include "ATrackSegment.h"
#include "GameFramework/CharacterMovementComponent.h" 
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "CharacterAnimInstance.h"
#include <ParkourPlayerController.h>

// Sets default values
AParkourCharacter::AParkourCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bIsIn2DMode = false;
	CurrentLaneIndex = 1;



	SpringArmFor3D = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmFor3D"));
	SpringArmFor3D->SetupAttachment(RootComponent);
	SpringArmFor3D->TargetArmLength = TargetArmLength;
	SpringArmFor3D->bEnableCameraLag = true;
	SpringArmFor3D->CameraLagSpeed = 10.0f;
	SpringArmFor3D->bUsePawnControlRotation = false;
	SpringArmFor3D->bInheritYaw = true;              // Follow character rotation on yaw
	SpringArmFor3D->bInheritPitch = false;           // Do not inherit pitch (up/down)
	SpringArmFor3D->bInheritRoll = false;            // Do not inherit roll

	CameraFor3D = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraFor3D"));
	CameraFor3D->SetupAttachment(SpringArmFor3D, USpringArmComponent::SocketName);
	CameraFor3D->bUsePawnControlRotation = false;


	SpringArmFor2D = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmFor2D"));
	SpringArmFor2D->SetupAttachment(RootComponent);
	SpringArmFor2D->TargetArmLength = 0.f;
	SpringArmFor2D->bEnableCameraLag = false;  // Disable lag for smooth movement (if enabled)
	SpringArmFor2D->bInheritPitch = false;     // Prevent pitch (vertical rotation)
	SpringArmFor2D->bInheritRoll = false;      // Prevent roll (side-to-side rotation)
	SpringArmFor2D->bUsePawnControlRotation = false;

	CameraFor2D = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraFor2D"));
	CameraFor2D->SetupAttachment(SpringArmFor2D, USpringArmComponent::SocketName);
	CameraFor2D->SetRelativeLocation(FVector(CameraLengthFor2D, CameraZFor2D, CameraHeightFor2D));
	CameraFor2D->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));


	bIsCrouching = false;
	bIsJumping = false;

}

// Called when the game starts or when spawned
void AParkourCharacter::BeginPlay()
{
	Super::BeginPlay();
	FindAllTrackSegments();
	LowestCameraHeight = 100.f;
	//LowestCameraHeightFor3D = 100.f;
	GetWorldTimerManager().SetTimer(SpeedTimerHandle, this, &AParkourCharacter::IncreaseMoveSpeed, SpeedInterval, true);
	CameraFor2D->SetRelativeLocation(FVector(CameraLengthFor2D, CameraZFor2D, CameraHeightFor2D));
	isFinished = false;


}

// Called every frame
void AParkourCharacter::Tick(float DeltaTime)
{

		FVector CameraLocation = CameraFor3D->GetComponentLocation();
		CameraLocation.Z = LowestCameraHeightFor3D;
		CameraFor3D->SetWorldLocation(CameraLocation);
	

	Super::Tick(DeltaTime);
	if (GetCharacterMovement()->IsFalling() == false)
	{
		if (bIsJumping)  
		{
			//SpringArmFor3D->bInheritPitch = true;
			//OnJumpRealesed();
		}
	}

	if (Controller && !isFinished)
	{
		//AddMovementInput(GetActorForwardVector(), 1.0f);
		MoveAlongSpline(DeltaTime);

	}

}

void AParkourCharacter::IncreaseMoveSpeed()
{
	MoveSpeed += SpeedIncrement;
	if (MoveSpeed >= MaxSpeed) {
		StopSpeedIncrease();
	}
}

void AParkourCharacter::StopSpeedIncrease()
{
	GetWorldTimerManager().ClearTimer(SpeedTimerHandle);

}

void AParkourCharacter::FindAllTrackSegments()
{
	TArray<AActor*> FoundTrackSegments;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AATrackSegment::StaticClass(), FoundTrackSegments);

	for (AActor* TrackSegmentActor : FoundTrackSegments)
	{
		AATrackSegment* TrackSegment = Cast<AATrackSegment>(TrackSegmentActor);
		if (TrackSegment)
		{
			// Add the TrackSegment to your TrackSegments array
			TrackSegmentsArray.Add(TrackSegment);
		}
	}

	TrackSegmentsArray.Sort([](const AATrackSegment& A, const AATrackSegment& B)
		{
			return A.GetSegmentValue() < B.GetSegmentValue();
		});
}


/// <summary>
/// Let Character move along the Splines
/// If you reach the end for this Spline, add the CurrentSegmentIndex for enter next Segment
/// </summary>
/// <param name="DeltaTime"></param>
void AParkourCharacter::MoveAlongSpline(float DeltaTime)
{
	if (TrackSegmentsArray.Num() == 0) return;
	if (CurrentSegmentIndex >= TrackSegmentsArray.Num()) {
		//TODO: Win
		AParkourPlayerController* MyPlayerController = Cast<AParkourPlayerController>(GetController());

		if (MyPlayerController)
		{
			MyPlayerController->HandleVictory();
			isFinished = true;
			TrackSegmentsArray.Empty();
		}
		return;
	}

	AATrackSegment* CurrentTrackSegment = TrackSegmentsArray[CurrentSegmentIndex];

	if (CurrentTrackSegment->bIsIn2DMode) {

		if (SplineProgress == 0.0f) {
			//LowestCameraHeight = CameraFor2D->GetComponentLocation().Z;
			SwitchLane(1);
		}
		SwitchTo2DMode(CurrentTrackSegment->bISfromRightSide);
	}
	else {
		SwitchTo3DMode();
	}

	if (SplineProgress == 0.0f) {
		UE_LOG(LogTemp, Warning, TEXT("%d"), CurrentTrackSegment->SegmentValue);

	}

	if (CurrentTrackSegment && CurrentTrackSegment->SplineComponent)
	{
		float SplineLength = CurrentTrackSegment->SplineComponent->GetSplineLength();
		//SplineProgress = FMath::FInterpTo(SplineProgress, SplineProgress + (MoveSpeed * DeltaTime), DeltaTime, InterpolateSpeed);
		SplineProgress += (MoveSpeed * DeltaTime);
		if (SplineProgress >= SplineLength)
		{
			CurrentSegmentIndex++;
			SplineProgress = 0.0f;
		}

		SetActorRotation(CurrentTrackSegment->SplineComponent->GetRotationAtDistanceAlongSpline(SplineProgress, ESplineCoordinateSpace::World));
		FVector SplineLocation = CurrentTrackSegment->SplineComponent->GetLocationAtDistanceAlongSpline(SplineProgress, ESplineCoordinateSpace::World);


		// Smooth lane transition
		CurrentLaneOffset = FMath::FInterpTo(CurrentLaneOffset, TargetLaneOffset, DeltaTime, InterpolateToLane);

		// Compute right vector for lane offset
		FVector SplineDirection = CurrentTrackSegment->SplineComponent->GetDirectionAtDistanceAlongSpline(SplineProgress, ESplineCoordinateSpace::World);
		FVector RightVector = FVector::CrossProduct(FVector::UpVector, SplineDirection).GetSafeNormal();


		// Apply lane offset
		//FVector TargetLocation = SplineLocation + (RightVector * CurrentLaneOffset);
		//FVector TargetLocation = SplineLocation + (RightVector * CurrentLaneOffset);
		FVector TargetLocation = SplineLocation + (RightVector * CurrentLaneOffset * CurrentTrackSegment->CurveMutipliers);

		FVector CurrentLocation = GetActorLocation();

		TargetLocation.Z = CurrentLocation.Z;
		
		SetActorLocation(TargetLocation);
		

	}
}

void AParkourCharacter::OnCrouchPressed()
{
	if (bIsJumping) return;
	Super::Crouch();
	bIsCrouching = true;
	GetWorldTimerManager().SetTimer(UncrouchTimer, this, &AParkourCharacter::OnCrouchReleased, uncrouchTime, false);

}

void AParkourCharacter::OnCrouchReleased()
{
	Super::UnCrouch();
	bIsCrouching = false;
}

void AParkourCharacter::OnJumpPressed()
{
	if (bIsCrouching) return;

	FVector CameraLocation = CameraFor3D->GetComponentLocation();
	LowestCameraHeightFor3D = CameraLocation.Z;
	GetWorldTimerManager().SetTimer(UnJumpTimer, this, &AParkourCharacter::OnJumpRealesed, unJumpTime, false);

	bIsJumping = true;
	bIsCrouching = false;

	//SpringArmFor3D->bInheritPitch = false;
	UCharacterMovementComponent* CharMovement = GetCharacterMovement();
	if (CharMovement)
	{
		CharMovement->JumpZVelocity = JumpVerlocity; // Adjust the height of the jump
		CharMovement->GravityScale = 1.5f;   // Adjust gravity (default is 1.0)
		Super::Jump();
	}
}

void AParkourCharacter::OnJumpRealesed()
{
	bIsJumping = false;
	StopJumping();
}

void AParkourCharacter::SwitchLane(int32 LaneIndex)
{
	if (LaneIndex < 0 || LaneIndex > MaxLaneIndex) return;
	if (bIsIn2DMode) {
		CurrentLaneIndex = 0;
	}
	else {
		CurrentLaneIndex = LaneIndex;
		TargetLaneOffset = (CurrentLaneIndex - 1) * LaneWidth;
	}
}

void AParkourCharacter::Attack()
{
	if (bIsAttacking || bIsJumping || bIsCrouched) return;
	GetWorldTimerManager().ClearTimer(AttackTimer);
	GetWorldTimerManager().SetTimer(AttackTimer, this, &AParkourCharacter::OnAttackFinished, attackTime, false);
	bIsAttacking = true;

}

void AParkourCharacter::OnAttackFinished()
{
	bIsAttacking = false;
}

void AParkourCharacter::SwitchTo3DMode()
{
	bIsIn2DMode = false;
	CameraFor3D->SetActive(true);
	CameraFor2D->SetActive(false);
	//LowestCameraHeight = 100.f;
	//UE_LOG(LogTemp, Log, TEXT("SwitchTo3DMode"));
	bIsJumping = false;
	bIsCrouched = false;

	if (LowestCameraHeightFor3D > CameraFor3D->GetComponentLocation().Z) {
		//LowestCameraHeightFor3D = CameraFor3D->GetComponentLocation().Z;
	}

}

void AParkourCharacter::SwitchTo2DMode(bool bISfromRightSide)
{
	bIsIn2DMode = true;
	if (SpringArmFor2D)
	{
		SpringArmFor2D->bEnableCameraLag = false;
		SpringArmFor2D->bInheritPitch = false;
		SpringArmFor2D->bInheritRoll = false;
		SpringArmFor2D->bUsePawnControlRotation = false;
	}
	if (bISfromRightSide) {
		CameraFor2D->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	}

	if (LowestCameraHeight > CameraFor2D->GetComponentLocation().Z) {
		//LowestCameraHeight = CameraFor2D->GetComponentLocation().Z;
	}

	FVector CameraLocation = CameraFor2D->GetComponentLocation();
	CameraLocation.Z = LowestCameraHeight;
	CameraFor2D->SetWorldLocation(CameraLocation);

	CameraFor3D->SetActive(false);
	CameraFor2D->SetActive(true);
}

void AParkourCharacter::ModifyHealth(float Amount)
{
	AParkourPlayerState* PS = GetPlayerState<AParkourPlayerState>();
	if (PS)
	{
		PS->AddHealth(Amount);
	}
}

void AParkourCharacter::ModifyScore(int32 Amount)
{
	AParkourPlayerState* PS = GetPlayerState<AParkourPlayerState>();
	if (PS)
	{
		PS->AddScore(Amount);
	}
}


