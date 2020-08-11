// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	if (bIsWinner)
	{
		UUserWidget* WinScreen = CreateWidget(this, WinGameClass);
		if (WinScreen)
		{
			WinScreen->AddToViewport();
		}
	}
	else
	{
		UUserWidget* LoseScreen = CreateWidget(this, LoseGameClass);
		if (LoseScreen)
		{
			LoseScreen->AddToViewport();
		}
	}

	HUDScreen->RemoveFromViewport();

	GetWorldTimerManager().SetTimer(EndGameTimer, this, &APlayerController::RestartLevel, RestartDelay);
}

void AShooterController::BeginPlay()
{
	if (GUIClass)
	{
		HUDScreen = CreateWidget(this, GUIClass);
		HUDScreen->AddToViewport();
	}
}
