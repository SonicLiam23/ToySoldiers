// Fill out your copyright notice in the Description page of Project Settings.


#include "EntityUpgradeComponent.h"
#include <string>
#include <sstream>

#define LEVEL_XP(x) ceil((gapBetweenLevels * pow(x, 2)) + xPNeededforLvlOne - gapBetweenLevels)

// Sets default values for this component's properties
UEntityUpgradeComponent::UEntityUpgradeComponent() : gapBetweenLevels(0.3f), xPNeededforLvlOne(3)
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
	StatData->NextLevelXP = LEVEL_XP(StatData->PlayerLevel);

}

void UEntityUpgradeComponent::LevelUp(int NewLevel)
{
	// subtract the current xp level from the current xp
	StatData->CurrentXP -= StatData->NextLevelXP;

	StatData->NextLevelXP = LEVEL_XP(NewLevel);

	


	Stat upgraded = StatData->GetRandomStat();

	*upgraded.statPtr += 0.1f; // increase the stat by 10%, can be changed to whatever you want
	OnLevelUp.Broadcast(NewLevel, upgraded.statName);
}

void UEntityUpgradeComponent::GainXP(float XPAmount)
{

	if (StatData == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("NO STATDATA"));
		return;
	}

	StatData->CurrentXP += XPAmount;
	OnGainXP.Broadcast(XPAmount);


	std::stringstream ss;
	ss << XPAmount;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, ss.str().c_str());


	// process all level ups
	while (StatData->CurrentXP >= StatData->NextLevelXP)
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

