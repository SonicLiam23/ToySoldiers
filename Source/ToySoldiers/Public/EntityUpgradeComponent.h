// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatMultipliers.h"

#include "EntityUpgradeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLevelUpSignature, int, NewLevel, FText, StatName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGainXPSignature, float, XPAmount);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOYSOLDIERS_API UEntityUpgradeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEntityUpgradeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;



public:	

	void LevelUp(int NewLevel);
	UPROPERTY(BlueprintAssignable, Category = "XP System")
	FOnLevelUpSignature OnLevelUp;

	void GainXP(float XPAmount);
	UPROPERTY(BlueprintAssignable, Category = "XP System")
	FOnGainXPSignature OnGainXP;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player Stats")
	UStatMultipliers* StatData;

	UFUNCTION(BlueprintPure, Category = "XP")
	float GetCurrentXPPercentage() const { return StatData->CurrentXP  / StatData->NextLevelXP; }
	UFUNCTION(BlueprintPure, Category = "XP")
	float GetCurrentXP() const { return StatData->CurrentXP; }
	UFUNCTION(BlueprintPure, Category = "XP")
	float GetMaxXP() const { return StatData->NextLevelXP; }

	// CONTAINS THE FORMULA FOR CALCULATING THE XP NEEDED FOR THE NEXT LEVEL, CAN BE CHANGED TO WHATEVER FORMULA YOU WANT
	// https://www.desmos.com/calculator/lw4roboaa0
	const float gapBetweenLevels = 0.3f; // please use the link to visualize this
	const int xPNeededforLvlOne = 3;
};
