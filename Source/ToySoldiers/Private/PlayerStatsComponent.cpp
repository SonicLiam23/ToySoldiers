// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatsComponent.h"

// Sets default values for this component's properties
UPlayerStatsComponent::UPlayerStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	StatData = CreateDefaultSubobject<UPlayerStats>(TEXT("PlayerStats"));
}


// Called when the game starts
void UPlayerStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UPlayerStatsComponent::LevelUp(int NewLevel)
{
	OnLevelUp.Broadcast(NewLevel);

	// CONTAINS THE FORMULA FOR CALCULATING THE XP NEEDED FOR THE NEXT LEVEL, CAN BE CHANGED TO WHATEVER FORMULA YOU WANT
	StatData->NextLevelXP = 100.f * FMath::Pow(1.5f, NewLevel - 1);
}

void UPlayerStatsComponent::GainXP(float XPAmount)
{
	StatData->CurrentXP += XPAmount;
	OnGainXP.Broadcast(XPAmount);

	if (StatData->CurrentXP >= StatData->NextLevelXP)
	{
		LevelUp(++StatData->PlayerLevel);
	}
}


// Called every frame
void UPlayerStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

