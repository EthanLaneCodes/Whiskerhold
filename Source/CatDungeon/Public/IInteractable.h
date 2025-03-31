// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IInteractable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UIInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CATDUNGEON_API IIInteractable
{
	GENERATED_BODY()

public:

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    void Activate(AActor* Interactor);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    void Deactivate();

    // Function to interact specifically with the player
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    void InteractWithPlayer(class AParkourCharacter* Player);

    // Float value for interaction effects (e.g., health boost, score increase, damage)
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    float GetInteractionValue();
};
