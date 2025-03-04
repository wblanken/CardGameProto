// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/CardActorBase.h"
#include "HeroCard.generated.h"

class UGameplayAbility;
class UGameplayEffect;
struct FHeroCardTableRow;
class UHeroCardWidgetController;
class UCardGameAttributeSet;
class UCardWidgetController;

UCLASS()
class CARDGAMEPROTO_API AHeroCard : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AHeroCard();

	UFUNCTION(BlueprintCallable)
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UFUNCTION(BlueprintNativeEvent)
	void SetIsAlterEgo(bool isAlterEgo);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCardGameAttributeSet> AttributeSet;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card UI")
	TObjectPtr<UHeroCardWidgetController> HeroCardWidgetController;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Card Data", meta=(RowType="HeroCardTableRow"))
	FDataTableRowHandle HeroCardData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card Data")
	TSubclassOf<UGameplayEffect> HeroAttributes;
	
	void ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& gameplayEffectClass, float level) const;
	virtual void InitializeDefaultAttributes() const;

	virtual void AddHeroAbilities();

private:

	bool IsAlterEgo {true};
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
};
