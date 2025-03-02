#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

struct FCardGameGameplayTags
{
public:
	static const FCardGameGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

	// Core attributes
	FGameplayTag Attributes_Core_HitPoints;
	FGameplayTag Attributes_Core_MaxHitPoints;
	FGameplayTag Attributes_Core_Attack;
	FGameplayTag Attributes_Core_Defense;
	FGameplayTag Attributes_Core_Thwart;
	FGameplayTag Attributes_Core_Recovery;
	FGameplayTag Attributes_Core_Scheme;

	// Basic Abilities
	FGameplayTag Abilities_Basic_Attack;
	FGameplayTag Abilities_Basic_Defend;
	FGameplayTag Abilities_Basic_Thwart;
	FGameplayTag Abilities_Basic_Recover;
	FGameplayTag Abilities_Basic_Scheme;
	FGameplayTag Abilities_Basic_ChangeForm;
	
	// Resources
	FGameplayTag Resources_Mental;
	FGameplayTag Resources_Energy;
	FGameplayTag Resources_Physical;
	FGameplayTag Resources_Wild;
	FGameplayTag Resources_Threat;
	FGameplayTag Resources_Acceleration;

	// Hero Tags
	FGameplayTag Hero_Hero;
	FGameplayTag Hero_Alter_Ego;
	FGameplayTag Hero_Ally;

	// Villain Tags
	FGameplayTag Villain_Villain;
	FGameplayTag Villain_Stage;
	FGameplayTag Villain_Scheme;
	FGameplayTag Villain_Minion;
	FGameplayTag Villain_Treachery;
	FGameplayTag Villain_Attachment;
	FGameplayTag Villain_SideScheme;
	FGameplayTag Villain_Crisis;
	FGameplayTag Villain_Acceleration;
	FGameplayTag Villain_Hazard;
	FGameplayTag Villain_Obligation;

private:
	static FCardGameGameplayTags GameplayTags;
};
