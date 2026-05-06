// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlayerStats.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TOYSOLDIERS_API UPlayerStats : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DamageMultiplier = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float FireRateMultiplier = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float SpeedMultiplier = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxHealthMultiplier = 1.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) 
	float CurrentXP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float NextLevelXP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int PlayerLevel;
};
