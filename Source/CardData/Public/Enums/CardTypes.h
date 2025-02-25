#pragma once

#include "CardTypes.generated.h"

UENUM(BlueprintType)
enum class ECardType : uint8
{
	Hero = 0,
	AlterEgo,
	Obligation,
	Ally,
	Attachment,
	Event,
	Resource,
	Support,
	Upgrade,
	Villain,
	MainScheme,
	SideScheme,
	Minion,
	Treachery,
	Environment
};

UENUM(BlueprintType)
enum class EHeroCardType : uint8
{
	Hero = ECardType::Hero,
	AlterEgo,
	Obligation,
	Ally,
	Attachment,
	Event,
	Resource,
	Support,
	Upgrade
};

UENUM(BlueprintType)
enum class EEncounterCardType : uint8
{
	Invalid = 0,
	Villain = ECardType::Villain,
	MainScheme,
	SideScheme,
	Minion,
	Treachery,
	Environment
};
