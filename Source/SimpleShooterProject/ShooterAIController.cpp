// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	PlayerRef = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (AIBehavior && PlayerRef)
	{
		RunBehaviorTree(AIBehavior);
		
		GetBlackboardComponent()->SetValueAsVector("StartLocation", GetPawn()->GetActorLocation());
	}
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (LineOfSightTo(PlayerRef))
	{
		GetBlackboardComponent()->SetValueAsVector("PlayerLocation", PlayerRef->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector("LastPlayerLocation", PlayerRef->GetActorLocation());
	}
	else
	{
		GetBlackboardComponent()->ClearValue("PlayerLocation");
	}
}

