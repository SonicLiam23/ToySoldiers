// Fill out your copyright notice in the Description page of Project Settings.
#include "StatMultipliers.h"
#include <random>

UStatMultipliers::UStatMultipliers()
{
	DamageMultiplier = 1.f;
	FireRateMultiplier = 1.f;
	MaxHealthMultiplier = 1.f;

	CurrentXP = 0.f;
	NextLevelXP = 0.f;
	PlayerLevel = 1.f;

}

Stat UStatMultipliers::GetRandomStat()
{
	Stat returnVal;

	srand(time(NULL));

	int stat = rand() % 4;

	switch (stat)
	{
	case 0:
		returnVal.statPtr = &DamageMultiplier;
		returnVal.statName = FText::FromString("Damage");
		return returnVal;
		break; // shouldnt need break but oh well

	case 1:
		returnVal.statPtr = &FireRateMultiplier;
		returnVal.statName = FText::FromString("Fire rate");
		return returnVal;
		break; // shouldnt need break but oh well

	case 2:
		returnVal.statPtr = &MaxHealthMultiplier;
		returnVal.statName = FText::FromString("Max health");
		return returnVal;
		break; // shouldnt need break but oh well
	}

	returnVal.statPtr = &DamageMultiplier;
	returnVal.statName = FText::FromString("Damage");
	return returnVal;
}
