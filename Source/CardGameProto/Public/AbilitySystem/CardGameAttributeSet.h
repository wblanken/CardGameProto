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

#define DECLARE_ATTRIBUTE(ClassName, PropertyName) \
	UFUNCTION() \
	void OnRep_##PropertyName(const FGameplayAttributeData& old##PropertyName) const; \
	FGameplayAttributeData PropertyName; \
	ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \

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
	TWeakObjectPtr<AController> Controller = nullptr;

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

/**
 * 
 */
UCLASS(Abstract)
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
	DECLARE_ATTRIBUTE(UCardGameAttributeSet, HitPoints);
	DECLARE_ATTRIBUTE(UCardGameAttributeSet, MaxHitPoints);
	DECLARE_ATTRIBUTE(UCardGameAttributeSet, Attack);
	DECLARE_ATTRIBUTE(UCardGameAttributeSet, Defense);
	DECLARE_ATTRIBUTE(UCardGameAttributeSet, Thwart);
	DECLARE_ATTRIBUTE(UCardGameAttributeSet, Recovery);
	DECLARE_ATTRIBUTE(UCardGameAttributeSet, Scheme);

private:
	void SetEffectProperties(const struct FGameplayEffectModCallbackData& Data, FEffectProperties& Props);
};

