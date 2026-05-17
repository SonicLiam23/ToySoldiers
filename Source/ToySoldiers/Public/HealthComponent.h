// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class UEntityUpgradeComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTakeDamageSignature, float, DamageAmount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealSignature, float, HealAmount, bool, IgnoreMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOYSOLDIERS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();
	UFUNCTION(BlueprintCallable, Category = "Health")
	void TakeDamage(float DamageAmount);
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnTakeDamageSignature OnTakeDamage;
	UFUNCTION(BlueprintCallable, Category = "Health")
	void Heal(float HealAmount, bool ignoreMaxHealth = false);
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealSignature OnHeal;

	void Die();
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnDeathSignature OnDeath;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercentage() const { return CurrentHealth / MaxHealth; }

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	bool AutoDestroyOnDeath = false;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	float MaxHealth = 100.f;
	float baseMaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	float CurrentHealth = 100.f;


	UFUNCTION()
	void HandleTakeAnyDamage(
		AActor* DamagedActor,
		float Damage,
		const UDamageType* DamageType,
		AController* InstigatedBy,
		AActor* DamageCauser
	);

	bool isOnPlayer;

	static UEntityUpgradeComponent* UpgradeComponent;

	// IM AWARE THIS IS IN THE WRONG PLACE AND ITS STUPID BUT THATS THE IDEA OF A PROTOTYPE I GUESS XD
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Experience")
	int XPValue;

	bool isDead;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	AActor* Owner;
};
