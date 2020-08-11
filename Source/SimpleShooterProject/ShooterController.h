// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterController.generated.h"


/**
 * 
 */
UCLASS()
class SIMPLESHOOTERPROJECT_API AShooterController : public APlayerController
{
	GENERATED_BODY()

public:
	void GameHasEnded(class AActor* EndGameFocus, bool bIsWinner) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float RestartDelay = 5.f;

	FTimerHandle EndGameTimer;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoseGameClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinGameClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> GUIClass;

	UUserWidget* HUDScreen;
	
};
