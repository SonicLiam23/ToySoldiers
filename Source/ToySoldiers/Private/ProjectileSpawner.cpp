// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileSpawner.h"

// Sets default values
UProjectileSpawner::UProjectileSpawner()
{
	ProjectileToSpawn = AProjectileBase::StaticClass();	
}

// Called when the game starts or when spawned
void UProjectileSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void UProjectileSpawner::SpawnProjectile()
{
	if (IsValid(ProjectileToSpawn))
	{
		AProjectileBase* spawned = GetWorld()->SpawnActorDeferred<AProjectileBase>(ProjectileToSpawn, GetComponentTransform());
		spawned->InstigatorController = GetOwner()->GetInstigatorController();
		spawned->FinishSpawning(GetComponentTransform());
	}
}

