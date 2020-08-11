// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

class USkeletalMeshComponent;

UCLASS()
class SIMPLESHOOTERPROJECT_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* GunMesh;

	void PullTrigger();

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditDefaultsOnly)
	float MaxRange = 500.f;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditDefaultsOnly)
	float Damage = 10.f;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* MuzzleSound;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* ImpactSound;

private:

	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);

	AController* GetOwnerController() const;

};
