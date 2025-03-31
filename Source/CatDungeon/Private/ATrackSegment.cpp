// Fill out your copyright notice in the Description page of Project Settings.


#include "ATrackSegment.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"

// Sets default values
AATrackSegment::AATrackSegment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
    SplineComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    if (SplineComponent)
    {
        SplineComponent->SetMobility(EComponentMobility::Movable);
    }

    TrackMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TrackMeshComponent"));
    RootComponent = TrackMeshComponent;
    TrackMeshComponent->SetMobility(EComponentMobility::Movable);
}

// Called when the game starts or when spawned
void AATrackSegment::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AATrackSegment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AATrackSegment::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    //CreateSplineMeshes();

}

/*
void AATrackSegment::CreateSplineMeshes()
{
    if (!SplineComponent) return;

    const int32 NumSegments = SplineComponent->GetNumberOfSplineSegments();

    for (int32 i = 0; i < NumSegments; i++)
    {
        USplineMeshComponent* SplineMesh = NewObject<USplineMeshComponent>(this);
        if (SplineMesh)
        {
            SplineMesh->SetMobility(EComponentMobility::Movable);
            SplineMesh->AttachToComponent(SplineComponent, FAttachmentTransformRules::KeepRelativeTransform);

            FVector StartPos, StartTangent, EndPos, EndTangent;
            SplineComponent->GetLocationAndTangentAtSplinePoint(i, StartPos, StartTangent, ESplineCoordinateSpace::Local);
            SplineComponent->GetLocationAndTangentAtSplinePoint(i + 1, EndPos, EndTangent, ESplineCoordinateSpace::Local);

            SplineMesh->SetStartAndEnd(StartPos, StartTangent, EndPos, EndTangent);

            // Assign a material (Make sure you have a material in your project)
            SplineMesh->SetMaterial(0, SplineMaterial);

            SplineMesh->RegisterComponent();
        }
    } */

