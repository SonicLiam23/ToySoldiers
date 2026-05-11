// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileSpawner.h"
#include "StatMultipliers.h"
#include "EntityUpgradeComponent.h"

// Sets default values
UProjectileSpawner::UProjectileSpawner()
{
	ProjectileToSpawn = AProjectileBase::StaticClass();	

	MaxBulletsPerSecond = 3.f;
	
}

// Called when the game starts or when spawned
void UProjectileSpawner::BeginPlay()
{
	Super::BeginPlay();

	//log to screen 
	timeBetweenShots = 1.f / MaxBulletsPerSecond;
	timeOfLastShot = 0.f;
	UEntityUpgradeComponent* upgradeComp = GetOwner()->FindComponentByClass<UEntityUpgradeComponent>();

	// random comment
	if (upgradeComp)
	{
		statMultipliers = upgradeComp->StatData;
	}
}

AProjectileBase* UProjectileSpawner::SpawnProjectile()
{
	if (timeOfLastShot + timeBetweenShots > GetWorld()->GetTimeSeconds())
	{
		return nullptr;
	}

	if (IsValid(ProjectileToSpawn))
	{
		AProjectileBase* spawned = GetWorld()->SpawnActorDeferred<AProjectileBase>(ProjectileToSpawn, GetComponentTransform());
		spawned->InstigatorController = GetOwner()->GetInstigatorController();
		spawned->FinishSpawning(GetComponentTransform());
		if (statMultipliers)
		{
			spawned->Damage *= statMultipliers->DamageMultiplier;
			// projectile stat multipliers can be added here as needed
		}

		timeOfLastShot = GetWorld()->GetTimeSeconds();
		return spawned;
	}
	return nullptr;
}

