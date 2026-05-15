// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EntityUpgradeComponent.h"
#include <sstream>
#include "StatMultipliers.h"

UEntityUpgradeComponent* UHealthComponent::UpgradeComponent;

// Sets default values for this component's properties
UHealthComponent::UHealthComponent() : isOnPlayer(false)
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
	std::stringstream ss;

	CurrentHealth -= DamageAmount;
	

	ss << CurrentHealth;
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, ss.str().c_str());

	if (CurrentHealth <= 0.f)
	{
		Die();
	}

	OnTakeDamage.Broadcast(DamageAmount);
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
	OnDeath.Broadcast();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Death"));
	if (!isOnPlayer)
	{
		if (UpgradeComponent == nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("No player stats found"));
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
	if (InstigatedBy != nullptr)
	{
		bool isProjectileFromPlayer;
		if (InstigatedBy->GetPawn() != nullptr)
		{
			isProjectileFromPlayer = InstigatedBy->GetPawn()->IsPlayerControlled();
		}
		else
		{
			
			// player will always have a pawn, but some AI might not, so if there is no pawn, assume its not from the player
			isProjectileFromPlayer = false;
		}

		if (isOnPlayer ^ isProjectileFromPlayer)
			TakeDamage(Damage);
	}
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

