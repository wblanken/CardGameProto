#pragma once

#include "Factions.generated.h"

UENUM(BlueprintType)
enum class EFaction : uint8
{
	Aggression,
	Justice,
	Encounter,
	Hero,
	Basic,
	Leadership,
	Protection,
	Campaign
};
