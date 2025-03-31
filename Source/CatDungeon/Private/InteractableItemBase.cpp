// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableItemBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "ParkourCharacter.h"
#include "ParkourPlayerState.h"
#include "Engine/Engine.h"

// Sets default values
AInteractableItemBase::AInteractableItemBase()
{
	PrimaryActorTick.bCanEverTick = true;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;
    MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision); // No physical collision

    // Create CollisionComponent for interaction detection
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerComponent"));
    CollisionComponent->SetupAttachment(RootComponent);
    CollisionComponent->InitSphereRadius(100.f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
    CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // Overlaps with characters

    // Bind the overlap event
    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AInteractableItemBase::OnOverlapBegin);

}

// Called when the game starts or when spawned
void AInteractableItemBase::BeginPlay()
{
	Super::BeginPlay();
	bIsActive = true;
}

// Called every frame
void AInteractableItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AInteractableItemBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this && bIsActive)
    {
        AParkourCharacter* Character = Cast<AParkourCharacter>(OtherActor);
        if (Character)
        {
			if (bIsKillable && Character->bIsAttacking)
			{
				KilledByPlayer(Character);
			}
            else {
                InteractWithPlayer_Implementation(Character);
            }
        }
    }
}



void AInteractableItemBase::Activate_Implementation(AActor* Interactor)
{
}

void AInteractableItemBase::Deactivate_Implementation()
{
}

void AInteractableItemBase::InteractWithPlayer_Implementation(AParkourCharacter* Player)
{
    UE_LOG(LogTemp, Warning, TEXT("Interacted with player: %s"), *Player->GetName());
    if (Player)
    {
        AParkourPlayerState* PS = Player->GetPlayerState<AParkourPlayerState>();
        if (PS)
        {
            PS->AddHealth(InteractionHealthValue);  // Example: Heals player
            if (!bIsKillable) {
                PS->AddScore(InteractionScoreValue);
            }// Example: Increases score
            bIsActive = false;
        }
    }
}

void AInteractableItemBase::KilledByPlayer(AParkourCharacter* Player)
{
    UE_LOG(LogTemp, Warning, TEXT("KilledByPlayer : %s"), *Player->GetName());
    if (Player)
    {
        AParkourPlayerState* PS = Player->GetPlayerState<AParkourPlayerState>();
        if (PS)
        {
            PS->AddScore(InteractionScoreValue);       // Example: Increases score
            bIsActive = false;
            bbeKilled = true;
        }
    }
}

float AInteractableItemBase::GetInteractionValue_Implementation()
{
	return 0.0f;
}

