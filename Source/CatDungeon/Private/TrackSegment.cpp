// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackSegment.h"
#include "Components/BoxComponent.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Components/SceneComponent.h"


// Sets default values
ATrackSegment::ATrackSegment()
{
	PrimaryActorTick.bCanEverTick = true;
    /*
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
    FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, true);
    SplineComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    if (SplineComponent)
    {
        SplineComponent->SetMobility(EComponentMobility::Movable);
    }
	StartTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("StartTrigger")); 
	StartTrigger->SetupAttachment(RootComponent);

	EndTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("EndTrigger"));
	EndTrigger->SetupAttachment(RootComponent);
    */
}

// Called when the game starts or when spawned
void ATrackSegment::BeginPlay()
{
	Super::BeginPlay();
	/*
	StartTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATrackSegment::OnTriggerBeginOverlap);
	StartTrigger->OnComponentEndOverlap.AddDynamic(this, &ATrackSegment::OnTriggerEndOverlap);


	EndTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATrackSegment::OnTriggerBeginOverlap);
	EndTrigger->OnComponentEndOverlap.AddDynamic(this, &ATrackSegment::OnTriggerEndOverlap);
    */
}

void ATrackSegment::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    //CreateSplineMeshes();

}

// Called every frame
void ATrackSegment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
/*
void ATrackSegment::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ATrackSegment::OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}


void ATrackSegment::CreateSplineMeshes()
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
    }
   
}
 */

