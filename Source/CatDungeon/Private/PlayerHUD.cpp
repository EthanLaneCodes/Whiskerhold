// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UPlayerHUD::UpdateHealth(float Health)
{
    SetHealthIcons(Health);
}

void UPlayerHUD::UpdateScore(int32 Score)
{
    if (ScoreText)
    {
        ScoreText->SetText(FText::Format(FText::FromString(" {0}"), FText::AsNumber(Score)));
    }
}


void UPlayerHUD::SetHealthIcons(float Health)
{
    int32 FullHearts = FMath::FloorToInt(Health / (MaxHealth / HeartIcons.Num()));

    int NumHearts = FMath::FloorToInt(Health / MaxHealth * 3);  // Assume 3 hearts for simplicity

    if (HeartIcon1)
    {
        HeartIcon1->SetVisibility(Health >= 1 ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    }
    if (HeartIcon2)
    {
        HeartIcon2->SetVisibility(Health >= 2 ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    }
    if (HeartIcon3)
    {
        HeartIcon3->SetVisibility(Health >= 3 ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    }
}


