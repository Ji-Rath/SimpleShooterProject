// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleShooterProjectGameModeBase.h"
#include "EliminateAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTERPROJECT_API AEliminateAllGameMode : public ASimpleShooterProjectGameModeBase
{
	GENERATED_BODY()
	

public:
	void PawnKilled(APawn* Pawn) override;

	void EndGame(bool PlayerWins);
};
