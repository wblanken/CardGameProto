// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/CardGameAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "CardGameGameplayTags.h"
#include "Net/UnrealNetwork.h"

UCardGameAttributeSet::UCardGameAttributeSet()
{
	const auto gameplayTags = FCardGameGameplayTags::Get();

	TagsToAttributes.Add(gameplayTags.Attributes_Core_HitPoints, GetHitPointsAttribute);
	TagsToAttributes.Add(gameplayTags.Attributes_Core_MaxHitPoints, GetMaxHitPointsAttribute);
	TagsToAttributes.Add(gameplayTags.Attributes_Core_Attack, GetAttackAttribute);
	TagsToAttributes.Add(gameplayTags.Attributes_Core_Defense, GetDefenseAttribute);
	TagsToAttributes.Add(gameplayTags.Attributes_Core_Thwart, GetThwartAttribute);
	TagsToAttributes.Add(gameplayTags.Attributes_Core_Recovery, GetRecoveryAttribute);
	TagsToAttributes.Add(gameplayTags.Attributes_Core_Scheme, GetSchemeAttribute);
}

void UCardGameAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UCardGameAttributeSet, HitPoints, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCardGameAttributeSet, MaxHitPoints, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCardGameAttributeSet, Attack, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCardGameAttributeSet, Defense, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCardGameAttributeSet, Thwart, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCardGameAttributeSet, Recovery, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCardGameAttributeSet, Scheme, COND_None, REPNOTIFY_Always);
}

void UCardGameAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHitPointsAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHitPoints());
	}
}

void UCardGameAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	FEffectProperties props;
	SetEffectProperties(Data, props);

	if (Data.EvaluatedData.Attribute == GetHitPointsAttribute())
	{
		SetHitPoints(FMath::Clamp(GetHitPoints(), 0.f, GetMaxHitPoints()));
		UE_LOG(LogTemp, Warning, TEXT("Changed HitPoints on %s, HitPoints: %f"), *props.Target.AvatarActor->GetName(), GetHitPoints());
	}
}

void UCardGameAttributeSet::SetEffectProperties(const struct FGameplayEffectModCallbackData& Data, FEffectProperties& Props)
{
	Super::PostGameplayEffectExecute(Data);

	Props.EffectContextHandle = Data.EffectSpec.GetContext();

	Props.Source.AbilitySystemComponent = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.Target.AvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.Target.Pawn = Cast<APawn>(Props.Target.AvatarActor);
		Props.Target.AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.Target.AvatarActor.Get());
	}
}


void UCardGameAttributeSet::OnRep_HitPoints(const FGameplayAttributeData& oldHitPoints) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCardGameAttributeSet, HitPoints, oldHitPoints);
}

void UCardGameAttributeSet::OnRep_MaxHitPoints(const FGameplayAttributeData& oldMaxHitPoints) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCardGameAttributeSet, MaxHitPoints, oldMaxHitPoints);
}

void UCardGameAttributeSet::OnRep_Attack(const FGameplayAttributeData& oldAttack) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCardGameAttributeSet, Attack, oldAttack);
}

void UCardGameAttributeSet::OnRep_Defense(const FGameplayAttributeData& oldDefense) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCardGameAttributeSet, Defense, oldDefense);
}

void UCardGameAttributeSet::OnRep_Thwart(const FGameplayAttributeData& oldThwart) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCardGameAttributeSet, Thwart, oldThwart);
}

void UCardGameAttributeSet::OnRep_Recovery(const FGameplayAttributeData& oldRecovery) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCardGameAttributeSet, Recovery, oldRecovery);
}

void UCardGameAttributeSet::OnRep_Scheme(const FGameplayAttributeData& oldScheme) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCardGameAttributeSet, Scheme, oldScheme);
}