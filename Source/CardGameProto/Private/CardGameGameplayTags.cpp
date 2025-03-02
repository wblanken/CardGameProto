#include "CardGameGameplayTags.h"

#include "GameplayTagsManager.h"

FCardGameGameplayTags FCardGameGameplayTags::GameplayTags;

void FCardGameGameplayTags::InitializeNativeGameplayTags()
{
	/**
	 *	Core attributes
	 */
	GameplayTags.Attributes_Core_HitPoints = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Core.Health"),
		FString("Amount of damage a character can sustain before elimination"));
	GameplayTags.Attributes_Core_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Core.Attack"),
		FString("Amount of damage a character can inflict by using a basic attack"));	
	GameplayTags.Attributes_Core_Defense = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Core.Defense"),
		FString("Amount of damage a character can prevent by defending against attacks"));	
	GameplayTags.Attributes_Core_Thwart = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Core.Thwart"),
		FString("Amount of thread a character can remove from a scheme by using basic thwart"));	
	GameplayTags.Attributes_Core_Scheme = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Core.Scheme"),
		FString("Amount of base threat an enemy can generate when scheming"));	
	GameplayTags.Attributes_Core_Recovery = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Core.Recovery"),
		FString("Amount of health a character can regain by performing a recovery action"));

	/**
	 * Basic Abilities
	 */
	GameplayTags.Abilities_Basic_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Basic.Attack"),
		FString(""));
	GameplayTags.Abilities_Basic_Defend = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Basic.Defend"),
		FString(""));
	GameplayTags.Abilities_Basic_Thwart = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Basic.Thwart"),
		FString(""));
	GameplayTags.Abilities_Basic_Recover = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Basic.Recover"),
		FString(""));
	GameplayTags.Abilities_Basic_Scheme = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Basic.Scheme"),
		FString(""));
	GameplayTags.Abilities_Basic_ChangeForm = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Basic.ChangeForm"),
		FString(""));

	/**
	 * Resources
	 */
	GameplayTags.Resources_Mental = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Resources.Mental"),
		FString(""));
	GameplayTags.Resources_Energy = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Resources.Energy"),
		FString(""));
	GameplayTags.Resources_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Resources.Physical"),
		FString(""));
	GameplayTags.Resources_Wild = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Resources.Wild"),
		FString(""));
	GameplayTags.Resources_Threat = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Resources.Threat"),
		FString(""));
	GameplayTags.Resources_Acceleration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Resources.Acceleration"),
		FString(""));

	/**
	 * Hero Tags
	 */
	GameplayTags.Hero_Hero = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Hero.Hero"));
	GameplayTags.Hero_Alter_Ego = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Hero.Alter_Ego"));
	GameplayTags.Hero_Ally = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Hero.Ally"));

	/**
	 * Villian Tags
	 */
	GameplayTags.Villain_Villain = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Villain.Villain"),
	FString(""));
	GameplayTags.Villain_Stage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Villain.Stage"),
		FString(""));
	GameplayTags.Villain_Scheme = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Villain.Scheme"),
		FString(""));
	GameplayTags.Villain_Minion = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Villain.Minion"),
		FString(""));
	GameplayTags.Villain_Treachery = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Villain.Treachery"),
		FString(""));
	GameplayTags.Villain_Attachment = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Villain.Attachment"),
		FString(""));
	GameplayTags.Villain_SideScheme = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Villain.SideScheme"),
		FString(""));
	GameplayTags.Villain_Crisis = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Villain.Crisis"),
		FString(""));
	GameplayTags.Villain_Acceleration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Villain.Acceleration"),
		FString(""));
	GameplayTags.Villain_Hazard = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Villain.Hazard"),
		FString(""));
	GameplayTags.Villain_Obligation = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Villain.Obligation"),
		FString(""));
}


