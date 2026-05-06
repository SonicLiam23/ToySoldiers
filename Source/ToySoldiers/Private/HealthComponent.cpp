// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
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
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Player health Setup!"));

	isOnPlayer = false;
	if (APawn* Pawn = Cast<APawn>(Owner))
	{
		if (Pawn->IsPlayerControlled())
		{
			isOnPlayer = true;
		}
	}
}

void UHealthComponent::TakeDamage(float DamageAmount)
{	
	CurrentHealth -= DamageAmount;
	OnTakeDamage.Broadcast(DamageAmount);
	if (CurrentHealth <= 0.f)
	{
		Die();
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
	OnDeath.Broadcast();

	if (!isOnPlayer)
	{
		// make player get XP, currently working on stats class
	}

	if (Owner && AutoDestroyOnDeath)
	{
		Owner->Destroy();
	}
}


void UHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	bool isProjectileFromPlayer = InstigatedBy->GetPawn()->IsPlayerControlled();

	if (isOnPlayer ^ isProjectileFromPlayer) return; // if the damage is from the same side, ignore it
	TakeDamage(Damage);
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

