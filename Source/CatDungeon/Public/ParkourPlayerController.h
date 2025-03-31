// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerHUD.h"
#include "ParkourPlayerController.generated.h"

/**
 * 1.receive input actions
 * 2. UI (pending)
 * 3. show/hide UUSerWidget (pending)
 * RPC send input to server (pending)
 */
UCLASS()
class CATDUNGEON_API AParkourPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	AParkourPlayerController();
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	/// <summary>
	/// bind with input actions
	/// </summary>
	virtual void SetupInputComponent() override;

	void SwitchLandLeft();
	void SwitchLandRight();
	void Jump();
	void CrouchPressed();
	void CrouchReleased();

	void Attack();
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	void GetPlayerState() const;
	void ReduceHealth(float Health);
	void AddHealth(float Health);

	void UpdateHUDHealth(float Health);
	void UpdateHUDScore(int Score);
	void HandleDeath();
	void HandleVictory();


	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* JumpSound;

	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* CrouchSound;

	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* AttackSound;

	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* HittedSound;

	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* AddHealthSound;

	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* ChangeLaneSound;

	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* RunningSound;
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UPlayerHUD> PlayerHUDClass;



	/// <summary>
	/// The actual widget instance that will be displayed in the player's screen
	/// </summary>
	UPROPERTY()
	class UPlayerHUD* PlayerHUDWidget;


	/// <summary>
	/// Called when the player spawns to create the HUD
	/// </summary>
	void CreateHUD();
private:
	class AParkourCharacter* ParkourCharacter;

	int32 currentScore = 0;

};
