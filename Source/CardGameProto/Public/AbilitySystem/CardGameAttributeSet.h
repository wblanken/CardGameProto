// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CardGameProto/CardGameProto.h"
#include "CardGameAttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_DELEGATE_RetVal(FGameplayAttribute, FAttributeSignature)

USTRUCT()
struct FActorEffectProperties
{
	GENERATED_BODY()

	UPROPERTY()
	TWeakObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY()
	TWeakObjectPtr<AActor> AvatarActor = nullptr;

	UPROPERTY()
	TWeakObjectPtr<APawn> Pawn = nullptr;	
};

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties(){};
	
	FGameplayEffectContextHandle EffectContextHandle;
	UPROPERTY()
	FActorEffectProperties Source;

	UPROPERTY()
	FActorEffectProperties Target;
};

typedef TStaticFuncPointer<FGameplayAttribute()> FAttributeFuncPointer;

UCLASS()
class CARDGAMEPROTO_API UCardGameAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UCardGameAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	TMap<FGameplayTag, FAttributeFuncPointer> TagsToAttributes;

	// Shared Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HitPoints, Category = "Shared Attributes")
	FGameplayAttributeData HitPoints; ATTRIBUTE_ACCESSORS(UCardGameAttributeSet, HitPoints)
	
	UFUNCTION()
	void OnRep_HitPoints(const FGameplayAttributeData& oldHitPoints) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHitPoints, Category = "Shared Attributes")
	FGameplayAttributeData MaxHitPoints;
	ATTRIBUTE_ACCESSORS(UCardGameAttributeSet, MaxHitPoints)

	UFUNCTION()
	void OnRep_MaxHitPoints(const FGameplayAttributeData& oldMaxHitPoints) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Attack, Category = "Shared Attributes")
	FGameplayAttributeData Attack;
	ATTRIBUTE_ACCESSORS(UCardGameAttributeSet, Attack)
	
	UFUNCTION()
	void OnRep_Attack(const FGameplayAttributeData& oldAttack) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Defense, Category = "Hero Attributes")
	FGameplayAttributeData Defense;
	ATTRIBUTE_ACCESSORS(UCardGameAttributeSet, Defense)

	UFUNCTION()
	void OnRep_Defense(const FGameplayAttributeData& oldDefense) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Thwart, Category = "Hero Attributes")
	FGameplayAttributeData Thwart;
	ATTRIBUTE_ACCESSORS(UCardGameAttributeSet, Thwart)
	
	UFUNCTION()
	void OnRep_Thwart(const FGameplayAttributeData& oldThwart) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Recovery, Category = "Hero Attributes")
	FGameplayAttributeData Recovery;
	ATTRIBUTE_ACCESSORS(UCardGameAttributeSet, Recovery)
	
	UFUNCTION()
	void OnRep_Recovery(const FGameplayAttributeData& oldRecovery) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Scheme, Category = "Villian Attributes")
	FGameplayAttributeData Scheme;
	ATTRIBUTE_ACCESSORS(UCardGameAttributeSet, Scheme)
	
	UFUNCTION()
	void OnRep_Scheme(const FGameplayAttributeData& oldScheme) const;

private:
	void SetEffectProperties(const struct FGameplayEffectModCallbackData& Data, FEffectProperties& Props);
};

