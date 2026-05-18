// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "StatMultipliers.generated.h"

struct Stat
{
	float* statPtr;
	FText statName;
};

/**
 * 
 */
UCLASS(BlueprintType)
class TOYSOLDIERS_API UStatMultipliers : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UStatMultipliers();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DamageMultiplier;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float FireRateMultiplier;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxHealthMultiplier;


	// not really stats

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float CurrentXP;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float NextLevelXP;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float PlayerLevel;

	Stat GetRandomStat();
};