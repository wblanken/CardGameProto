// Copyright Will Blankenship 2024

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CardGameAbilitySystemComponent.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /** Asset Tags */);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CARDGAMEPROTO_API UCardGameAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void AbilityActorInfoSet();
	FEffectAssetTags EffectAssetTags;

	void AddCardAbilities(const TArray<TSubclassOf<UGameplayAbility>>& startupAbilities);

	void AbilityInputTagHeld(const FGameplayTag& inputTag);
	void AbilityInputTagReleased(const FGameplayTag& inputTag);
	
protected:
	UFUNCTION(Client, Reliable)
	void ClientEffectSpecApplied(UAbilitySystemComponent* abilitySystemComponent, const FGameplayEffectSpec& spec, FActiveGameplayEffectHandle handle);
};
