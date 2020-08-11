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

	if (MuzzleSound)
	{
		UGameplayStatics::SpawnSoundAttached(MuzzleSound, GunMesh, TEXT("MuzzleFlashSocket"));
	}

	FHitResult Hit = FHitResult();
	FVector ShotDirection = FVector();

	if (GunTrace(Hit, ShotDirection))
	{
		//Draw debug point
		DrawDebugPoint(GetWorld(), Hit.ImpactPoint, 5.f, FColor::Red, false, 10.f);

		//Spawn impact particle effect
		if (ImpactEffect)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation(), true);
		}

		if (ImpactSound)
		{
			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactSound, Hit.ImpactPoint);
		}

		//Deal Damage
		if (AActor* HitActor = Hit.GetActor())
		{
			FPointDamageEvent PointDamage = FPointDamageEvent(Damage, Hit, -ShotDirection, nullptr);
			AController* OwnerController = GetOwnerController();
			if (OwnerController)
			{
				HitActor->TakeDamage(Damage, PointDamage, OwnerController, this);
			}
		}
	}
}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if (!OwnerController) {return false;}

	FVector PlayerLocation;
	FRotator PlayerRotation;
	OwnerController->GetPlayerViewPoint(PlayerLocation, PlayerRotation);

	//DrawDebugCamera(GetWorld(), PlayerLocation, PlayerRotation, 90.f, 1.f, FColor::Red, false, 5.f);

	ShotDirection = PlayerRotation.Vector();
	FVector End = PlayerLocation + (ShotDirection * MaxRange);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(Hit, PlayerLocation, End, ECC_Visibility, Params);
}

AController* AGun::GetOwnerController() const
{
	APawn* PlayerPawn = Cast<APawn>(GetOwner());
	if (!PlayerPawn) { return nullptr; }

	AController* PlayerController = PlayerPawn->GetController();

	return PlayerController;
}

