// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SimpleShooterProjectGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTERPROJECT_API ASimpleShooterProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void PawnKilled(APawn* Pawn);
};
