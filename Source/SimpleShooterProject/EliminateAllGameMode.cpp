// Fill out your copyright notice in the Description page of Project Settings.


#include "EliminateAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void AEliminateAllGameMode::PawnKilled(APawn* Pawn)
{
	Super::PawnKilled(Pawn);

	APlayerController* PlayerController = Cast<APlayerController>(Pawn->GetController());

	//If player has died, player has lost
	if (Pawn && PlayerController)
	{
		EndGame(false);
	}

	for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
	{
		if (!Controller->IsDead())
		{
			return;
		}
	}

	EndGame(true);
}

void AEliminateAllGameMode::EndGame(bool PlayerWins)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == PlayerWins;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}

