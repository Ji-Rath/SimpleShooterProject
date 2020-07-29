 // Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene Component");
	SetRootComponent(SceneComponent);

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	GunMesh->SetupAttachment(SceneComponent);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	if (MuzzleFlash)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, GunMesh, TEXT("MuzzleFlashSocket"));
	}

	APawn* PlayerPawn = Cast<APawn>(GetOwner());
	if(!PlayerPawn) {return;}

	AController* PlayerController = PlayerPawn->GetController();
	if(!PlayerController) {return;}

	FVector PlayerLocation;
	FRotator PlayerRotation;
	PlayerController->GetPlayerViewPoint(PlayerLocation, PlayerRotation);

	DrawDebugCamera(GetWorld(), PlayerLocation, PlayerRotation, 90.f, 1.f, FColor::Red, false, 5.f);

	FVector End = PlayerLocation + (PlayerRotation.Vector() * MaxRange);
	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, PlayerLocation, End, ECC_Visibility))
	{
		//Draw debug point
		DrawDebugPoint(GetWorld(), Hit.ImpactPoint, 5.f, FColor::Red, false, 10.f);

		//Spawn impact particle effect
		if (ImpactEffect)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation(), true);
		}

		//Deal Damage
		if (AActor* HitActor = Hit.GetActor())
		{
			FPointDamageEvent PointDamage = FPointDamageEvent(10.f, Hit, -PlayerRotation.Vector(), nullptr);
			HitActor->TakeDamage(10.f, PointDamage, PlayerController, this);
		}
	}
}

