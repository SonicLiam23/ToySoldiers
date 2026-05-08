// Fill out your copyright notice in the Description page of Project Settings.


#include "EntityUpgradeComponent.h"

// Sets default values for this component's properties
UEntityUpgradeComponent::UEntityUpgradeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	StatData = CreateDefaultSubobject<UStatMultipliers>(TEXT("PlayerStats"));
}


// Called when the game starts
void UEntityUpgradeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UEntityUpgradeComponent::LevelUp(int NewLevel)
{
	OnLevelUp.Broadcast(NewLevel);

	// CONTAINS THE FORMULA FOR CALCULATING THE XP NEEDED FOR THE NEXT LEVEL, CAN BE CHANGED TO WHATEVER FORMULA YOU WANT
	// https://www.desmos.com/calculator/lw4roboaa0
	float gapBetweenLevels = 1; // given the equation is exponential. This increases the gap between levels by (gapBetweelLevels * 2) + 1. E.g if this is set to 1. Level 1 takes 1 xp, then 4, then 9 etc
	StatData->NextLevelXP = 100.f * FMath::Pow(1.5f, NewLevel - 1);
}

void UEntityUpgradeComponent::GainXP(float XPAmount)
{
	StatData->CurrentXP += XPAmount;
	OnGainXP.Broadcast(XPAmount);

	if (StatData->CurrentXP >= StatData->NextLevelXP)
	{
		LevelUp(++StatData->PlayerLevel);
	}
}


// Called every frame
void UEntityUpgradeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

