// Copyright Will Blankenship 2024


#include "Card/Widget/HeroCardWidgetController.h"

#include "AbilitySystem/CardGameAttributeSet.h"

void UHeroCardWidgetController::BroadcastInitialValues()
{
	const auto attributeSet = CastChecked<UCardGameAttributeSet>(AttributeSet);

	OnThwartChanged.Broadcast(attributeSet->GetThwart());
	OnAttackChanged.Broadcast(attributeSet->GetAttack());
	OnDefenseChanged.Broadcast(attributeSet->GetDefense());
	OnRecoveryChanged.Broadcast(attributeSet->GetRecovery());	
}

void UHeroCardWidgetController::BindCallbacksToDependencies()
{
	const auto attributeSet = CastChecked<UCardGameAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		attributeSet->GetThwartAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& data)
			{
				OnThwartChanged.Broadcast(data.NewValue);
			});
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		attributeSet->GetAttackAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& data)
			{
				OnAttackChanged.Broadcast(data.NewValue);
			});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		attributeSet->GetDefenseAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& data)
			{
				OnDefenseChanged.Broadcast(data.NewValue);
			});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		attributeSet->GetRecoveryAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& data)
			{
				OnRecoveryChanged.Broadcast(data.NewValue);
			});
}
