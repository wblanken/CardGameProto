#pragma once

#include "CardSetType.generated.h"

UENUM(BlueprintType)
enum class ECardSetType : uint8
{
	None,
	Basic,
	Aspect,
	Hero,
	Expert,
	Modular,
	Nemesis,
	Standard,
	Villain
};