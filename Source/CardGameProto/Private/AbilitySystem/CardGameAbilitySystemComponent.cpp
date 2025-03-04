// Copyright Will Blankenship 2024


#include "AbilitySystem/CardGameAbilitySystemComponent.h"

#include "AbilitySystem/Abilities/CardGameGameplayAbility.h"


void UCardGameAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UCardGameAbilitySystemComponent::ClientEffectSpecApplied);
}

void UCardGameAbilitySystemComponent::AddCardAbilities(const TArray<TSubclassOf<UGameplayAbility>>& startupAbilities)
{
	for (const auto abilityClass : startupAbilities)
	{
		auto abilitySpec = FGameplayAbilitySpec(abilityClass, 1);
		GiveAbility(abilitySpec);
		/*if (const auto* ability = Cast<UCardGameGameplayAbility>(abilitySpec.Ability))
		{
			//abilitySpec.DynamicAbilityTags.AddTag(ability->)
			
		}*/	
	}
}

void UCardGameAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& inputTag)
{
	if (!inputTag.IsValid()) return;
	for (auto& abilitySpec : GetActivatableAbilities())
	{
		if (abilitySpec.GetDynamicSpecSourceTags().HasTagExact(inputTag))
		{
			AbilitySpecInputPressed(abilitySpec);
			if (!abilitySpec.IsActive())
			{
				TryActivateAbility(abilitySpec.Handle);
			}
		}
	}
}

void UCardGameAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& inputTag)
{
	if (!inputTag.IsValid()) return;
	for (auto& abilitySpec : GetActivatableAbilities())
	{
		if (abilitySpec.GetDynamicSpecSourceTags().HasTagExact(inputTag))
		{
			AbilitySpecInputReleased(abilitySpec);
		}
	}
}

void UCardGameAbilitySystemComponent::ClientEffectSpecApplied_Implementation(
	UAbilitySystemComponent* abilitySystemComponent, const FGameplayEffectSpec& spec,
	FActiveGameplayEffectHandle handle)
{
	FGameplayTagContainer tagContainer;
	spec.GetAllAssetTags(tagContainer);

	EffectAssetTags.Broadcast(tagContainer);
}