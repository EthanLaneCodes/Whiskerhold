#include "ParkourPlayerController.h"
#include "CoreMinimal.h"
#include "ParkourCharacter.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.h"


#include "Kismet/GameplayStatics.h"




AParkourPlayerController::AParkourPlayerController()
{
}

void AParkourPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ParkourCharacter = Cast<AParkourCharacter>(GetCharacter());
	if (PlayerHUDClass)
	{
		CreateHUD();
	}

	if (RunningSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, RunningSound, ParkourCharacter->GetActorLocation());
	}

}

void AParkourPlayerController::Tick(float DeltaTime)
{
}

void AParkourPlayerController::CreateHUD()
{
	if (PlayerHUDClass)
	{
		PlayerHUDWidget = CreateWidget<UPlayerHUD>(this, PlayerHUDClass); // Create the widget
		if (PlayerHUDWidget) // Check if the widget was created successfully
		{
			PlayerHUDWidget->AddToViewport(); // Add the widget to the viewport to show it
		}
	}

	
}

void AParkourPlayerController::GetPlayerState() const
{
}

void AParkourPlayerController::ReduceHealth(float Health)
{
	UpdateHUDHealth(Health);
	if (HittedSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HittedSound, ParkourCharacter->GetActorLocation());
	}
}

void AParkourPlayerController::AddHealth(float Health)
{
	UpdateHUDHealth(Health);
}


void AParkourPlayerController::UpdateHUDHealth(float Health)
{
	if (PlayerHUDWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("UpdateHUDHealth: %f"), Health);
		PlayerHUDWidget->UpdateHealth(Health);
	}
}

void AParkourPlayerController::UpdateHUDScore(int Score)
{
	if (PlayerHUDWidget)
	{
		PlayerHUDWidget->UpdateScore(Score);
		currentScore = Score;
	}
}

void AParkourPlayerController::HandleDeath()
{

}

void AParkourPlayerController::HandleVictory()
{

}



/// <summary>
/// bind with input actions
/// </summary>
void AParkourPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("SwitchLandLeft", IE_Pressed, this, &AParkourPlayerController::SwitchLandLeft);
	InputComponent->BindAction("SwitchLandRight", IE_Pressed, this, &AParkourPlayerController::SwitchLandRight);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AParkourPlayerController::Jump);
	InputComponent->BindAction("Crouch", IE_Pressed, this, &AParkourPlayerController::CrouchPressed);
	InputComponent->BindAction("Crouch", IE_Released, this, &AParkourPlayerController::CrouchReleased);
	InputComponent->BindAction("Attack", IE_Pressed, this, &AParkourPlayerController::Attack);
}

void AParkourPlayerController::SwitchLandLeft()
{
	if (ParkourCharacter)
	{
		ParkourCharacter->SwitchLane(ParkourCharacter->GetCurrentLaneIndex() - 1);
		if (ChangeLaneSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ChangeLaneSound, ParkourCharacter->GetActorLocation());
		}
	}
}

void AParkourPlayerController::SwitchLandRight()
{
	if (ParkourCharacter)
	{
		ParkourCharacter->SwitchLane(ParkourCharacter->GetCurrentLaneIndex() + 1);
		if (ChangeLaneSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ChangeLaneSound, ParkourCharacter->GetActorLocation());
		}
	}
}

void AParkourPlayerController::Jump()
{
	if (ParkourCharacter)
	{
		ParkourCharacter->OnJumpPressed();
		if (JumpSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, JumpSound, ParkourCharacter->GetActorLocation());
		}
	}
}

void AParkourPlayerController::CrouchPressed()
{
	if (ParkourCharacter)
	{
		ParkourCharacter->OnCrouchPressed();
		if (CrouchSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, CrouchSound, ParkourCharacter->GetActorLocation());
		}
	}
}

void AParkourPlayerController::CrouchReleased()
{
	if (ParkourCharacter)
	{
		//ParkourCharacter->OnCrouchReleased();
	}
}

void AParkourPlayerController::Attack()
{
	if (ParkourCharacter)
	{

		if (AttackSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, AttackSound, ParkourCharacter->GetActorLocation());
		}
		ParkourCharacter->Attack();
	}
}
