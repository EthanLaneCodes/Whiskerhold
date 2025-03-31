// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h" 

#include "ATrackSegment.generated.h"

UCLASS()
class CATDUNGEON_API AATrackSegment : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AATrackSegment();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	//void CreateSplineMeshes();
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spline", meta = (AllowPrivateAccess = "true"))
	USplineComponent* SplineComponent;

	// Integer value to be used for sorting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Track Segment")
	int SegmentValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lane")
	int CurveMutipliers = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lane")
	bool bIsIn2DMode = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lane")
	bool bISfromRightSide = true;

	// Static Mesh Component (Movable)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	class UStaticMeshComponent* TrackMeshComponent;

	int GetSegmentValue() const { return SegmentValue; }

	// Setter for SegmentValue
	void SetSegmentValue(int NewValue) { SegmentValue = NewValue; }
};
