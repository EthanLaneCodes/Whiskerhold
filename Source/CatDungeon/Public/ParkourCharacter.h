// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ParkourCharacter.generated.h"

UCLASS()
class CATDUNGEON_API AParkourCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AParkourCharacter();
	bool bIsCrouching;
	bool bIsJumping;
	bool bIsAttacking;

protected:
	virtual void BeginPlay() override;



public:	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	/// <summary>
	/// Movement speed along the spline
	/// </summary>
	float MoveSpeed = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SpeedIncrement = 50.0f; // Speed added each time interval

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SpeedInterval = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MaxSpeed = 800.0f; // Speed added each time interval

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float JumpVerlocity = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float InterpolateSpeed = 5.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float uncrouchTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float unJumpTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float attackTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lane")
	int32 MaxLaneIndex = 2;

	/// <summary>
	/// Width between lanes
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lane")
	float LaneWidth = 2000.0f;

	/// <summary>
	/// The target offset for smooth interpolation
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lane")
	float InterpolateToLane = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	/// <summary>
	/// 
	/// </summary>
	float TargetArmLength = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "2DCamera")
	/// <summary>
	/// 
	/// </summary>
	float CameraLengthFor2D = -100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "2DCamera")
	/// <summary>
	/// 
	/// </summary>
	float CameraZFor2D = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "2DCamera")
	/// <summary>
	/// 
	/// </summary>
	float CameraHeightFor2D = 300.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))

	float LowestCameraHeightFor3D = 300.f;

	/// <summary>
	/// Spline references (array of track segments)
	/// </summary>
	TArray<class AATrackSegment*> TrackSegmentsArray;

	/// <summary>
	/// To keep track of current position along the spline
	/// </summary>
	float SplineProgress = 0.0f;

	/// <summary>
	/// Record the gameMode
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "2D")
	bool bIsIn2DMode;


	/// <summary>
	/// 0: Left, 1: middle, 2: Right
	/// </summary>
	/// <returns></returns>
	int32 GetCurrentLaneIndex() const { return CurrentLaneIndex; }

	void OnCrouchPressed();
	void OnCrouchReleased();
	void OnJumpPressed();
	void OnJumpRealesed();
	void OnAttackFinished();


	void Attack();
	void SwitchLane(int32 LandIndex);

	void ModifyHealth(float Amount);
	void ModifyScore(int32 Amount);

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmFor3D;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmFor2D;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraFor3D;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraFor2D;

	int32 CurrentLaneIndex;
	int32 CurrentSegmentIndex;
	
	float CurrentLaneOffset;
	float TargetLaneOffset;
	float LowestCameraHeight;

	float JumpTimer;
	FTimerHandle UncrouchTimer;
	FTimerHandle UnJumpTimer;
	FTimerHandle AttackTimer;

	void SwitchTo3DMode();
	void SwitchTo2DMode(bool bISfromRightSide);
	void MoveAlongSpline(float DeltaTime);
	void FindAllTrackSegments();
	FTimerHandle SpeedTimerHandle;

	// Function to increase speed
	void IncreaseMoveSpeed();

	// Function to stop the speed increase
	void StopSpeedIncrease();

	bool isFinished = false;

};
