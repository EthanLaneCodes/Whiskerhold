// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ParkourPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class CATDUNGEON_API AParkourPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:

    /// <summary>
    /// the number of hearts
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    float MaxHealth = 3.0f;

    // Health of the player
    UPROPERTY(BlueprintReadWrite, Category = "PlayerStats")
    float Health;

    UPROPERTY(BlueprintReadWrite, Category = "Score")
    int32 ScoreIncrement = 1;  //

    UPROPERTY(BlueprintReadWrite, Category = "Score")
    float ScoreInterval = 0.5f;

    // Function to add health
    UFUNCTION(BlueprintCallable, Category = "PlayerStats")
    void AddHealth(float Amount);

    // Function to add score
    UFUNCTION(BlueprintCallable, Category = "PlayerStats")
    void AddScore(int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "PlayerStats")
    void Victory();

    void NotifyHealthAdded();
    void NotifyHealthReduced();

    void NotifyScoreChanged();


protected:
    virtual void BeginPlay() override;
private:

    UFUNCTION(BlueprintCallable, Category = "PlayerStats")
    void Die();

    void StartScoring();
    void IncreaseScore();

    FTimerHandle ScoreTimerHandle; 

};
