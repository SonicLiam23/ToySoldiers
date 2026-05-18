// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EntityUpgradeComponent.h"
#include <sstream>
#include "StatMultipliers.h"

UEntityUpgradeComponent* UHealthComponent::UpgradeComponent;

// Sets default values for this component's properties
UHealthComponent::UHealthComponent() : isOnPlayer(false), isDead(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Owner = GetOwner();
	Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::HandleTakeAnyDamage);

	isOnPlayer = false;
	if (APawn* Pawn = Cast<APawn>(Owner))
	{
		if (Pawn->IsPlayerControlled())
		{
			isOnPlayer = true;
			UpgradeComponent = Cast<UEntityUpgradeComponent>(Pawn->GetComponentByClass(UEntityUpgradeComponent::StaticClass()));
		}
	}

	baseMaxHealth = MaxHealth;
}

void UHealthComponent::TakeDamage(float DamageAmount)
{	
	if (!isDead)
	{
		CurrentHealth -= DamageAmount;
		OnTakeDamage.Broadcast(DamageAmount);
		if (CurrentHealth <= 0.f)
		{
			Die();
		}
	}
}

void UHealthComponent::Heal(float HealAmount, bool ignoreMaxHealth)
{
	CurrentHealth += HealAmount;
	OnHeal.Broadcast(HealAmount, ignoreMaxHealth);
	if (!ignoreMaxHealth && CurrentHealth > MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
}

void UHealthComponent::Die()
{
	if (isDead)
	{
		return;
	}
	isDead = true;

	OnDeath.Broadcast();

	if (!isOnPlayer)
	{
		if (UpgradeComponent == nullptr)
		{
			return;
		}
		UpgradeComponent->GainXP(XPValue);
	}

	if (Owner && AutoDestroyOnDeath)
	{
		Owner->Destroy();
	}
}


void UHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (InstigatedBy == nullptr)
	{
		// if there is no instigator, ignore the damage
		return;
	}
	bool isProjectileFromPlayer = InstigatedBy->GetPawn()->IsPlayerControlled();

	if (isOnPlayer ^ isProjectileFromPlayer) 
		TakeDamage(Damage);
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (UpgradeComponent != nullptr)
	{
		// MaxHealth = baseMaxHealth * UpgradeComponent->StatData->MaxHealthMultiplier;
	}
}

