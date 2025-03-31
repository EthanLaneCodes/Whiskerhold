// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class CATDUNGEON_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateHealth(float Health);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateScore(int32 Score);

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ScoreText;

    // Array of heart icon widgets to represent health
    UPROPERTY(meta = (BindWidget))
    TArray<class UImage*> HeartIcons;

    UPROPERTY(meta = (BindWidget))
    UImage* HeartIcon1;

    UPROPERTY(meta = (BindWidget))
    UImage* HeartIcon2;

    UPROPERTY(meta = (BindWidget))
    UImage* HeartIcon3;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    UTexture2D* FullHeartIcon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    UTexture2D* EmptyHeartIcon;

    /// <summary>
    /// the number of hearts
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    float MaxHealth = 3.0f;

private:
    void SetHealthIcons(float Health);
};
