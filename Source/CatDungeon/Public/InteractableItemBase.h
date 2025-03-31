// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IInteractable.h"
#include "InteractableItemBase.generated.h"

UCLASS()
class CATDUNGEON_API AInteractableItemBase : public AActor, public IIInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	virtual void Activate_Implementation(AActor* Interactor) override;

	virtual void Deactivate_Implementation() override;

	// Implement InteractWithPlayer function from the interface
	virtual void InteractWithPlayer_Implementation(class AParkourCharacter* Player) override;

	void KilledByPlayer(class AParkourCharacter* Player);

	// Implement GetInteractionValue function from the interface
	virtual float GetInteractionValue_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
	bool bIsKillable = false; //

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
	bool bIsActive = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
	bool bbeKilled = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* MeshComponent;

	/// <summary>
	/// Collision component for detecting overlaps
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	class USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InteractionValue")
	float InteractionHealthValue = -1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InteractionValue")
	float InteractionScoreValue = 5.0f;

private:
};
