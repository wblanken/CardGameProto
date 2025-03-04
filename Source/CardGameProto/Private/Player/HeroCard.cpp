// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HeroCard.h"

#include "AttributeSet.h"
#include "CardGameGameplayTags.h"
#include "AbilitySystem/CardGameAbilitySystemComponent.h"
#include "AbilitySystem/CardGameAttributeSet.h"
#include "AbilitySystem/Data/CardDataTable.h"
#include "Card/Widget/HeroCardWidgetController.h"

// Sets default values
AHeroCard::AHeroCard()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent = CreateDefaultSubobject<UCardGameAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);

	AttributeSet = CreateDefaultSubobject<UCardGameAttributeSet>("HeroAttributeSet");
	HeroCardWidgetController = CreateDefaultSubobject<UHeroCardWidgetController>("HeroCardWidgetController");
}

UAbilitySystemComponent* AHeroCard::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AHeroCard::SetIsAlterEgo_Implementation(bool isAlterEgo)
{
	IsAlterEgo = isAlterEgo;
}

// Called when the game starts or when spawned
void AHeroCard::BeginPlay()
{
	Super::BeginPlay();

	InitializeDefaultAttributes();
	
	if (HeroCardWidgetController)
	{
		const FWidgetControllerParams params(AbilitySystemComponent.Get(), AttributeSet.Get());
		HeroCardWidgetController->SetWidgetControllerParams(params);
		HeroCardWidgetController->BindCallbacksToDependencies();
	}
	
	// Make sure we're set to the Alter-Ego side and set up the data for it.
	if (!IsAlterEgo)
	{
		SetIsAlterEgo(true);
	}

	HeroCardWidgetController->BroadcastInitialValues();
}

void AHeroCard::ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& gameplayEffectClass, float level) const
{
	check(AbilitySystemComponent);
	check(gameplayEffectClass);

	auto contextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	contextHandle.AddSourceObject(this);
	const auto specHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(gameplayEffectClass, level, contextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*specHandle.Data, GetAbilitySystemComponent());
}

void AHeroCard::InitializeDefaultAttributes() const
{
	check(!HeroCardData.IsNull());
	auto heroCardData = HeroCardData.GetRow<FHeroCardTableRow>(TEXT("AHeroCard::InitializeDefaultAttributes - Loading Hero Data"));

	// Setup the initial values for our attributes based on our hero data
	check(AbilitySystemComponent);
	check(HeroAttributes);

	const auto gameplayTags = FCardGameGameplayTags::Get();
	
	auto contextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	contextHandle.AddSourceObject(this);
	const auto specHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(HeroAttributes.Get(), 1.f, contextHandle);

	specHandle.Data->SetSetByCallerMagnitude(gameplayTags.Attributes_Core_Thwart, heroCardData->Thwart);
	specHandle.Data->SetSetByCallerMagnitude(gameplayTags.Attributes_Core_Attack, heroCardData->Attack);
	specHandle.Data->SetSetByCallerMagnitude(gameplayTags.Attributes_Core_Defense, heroCardData->Defense);
	specHandle.Data->SetSetByCallerMagnitude(gameplayTags.Attributes_Core_Recovery, heroCardData->Recover);
	
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*specHandle.Data, AbilitySystemComponent);
}

void AHeroCard::AddHeroAbilities()
{
	if (!HasAuthority()) return;

	const auto asc = CastChecked<UCardGameAbilitySystemComponent>(AbilitySystemComponent);
	asc->AddCardAbilities(StartupAbilities);
}

