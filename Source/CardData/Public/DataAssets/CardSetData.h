// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/CardSetType.h"
#include "Enums/CardTypes.h"

#include "CardSetData.generated.h"

struct FResourceCost;
class UCardSetData;
class UHeroIdentityCardData;
class UHeroObligationCardData;
class UHeroPackCard;
class UNemesisCardData;

UCLASS()
class CARDDATA_API UPackDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString PackName{};
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSoftObjectPtr<UCardSetData>> CardSets;
};

UCLASS(Abstract)
class CARDDATA_API UCardSetData : public UDataAsset
{
	GENERATED_BODY()

public:
	UCardSetData() = default;
	
	explicit UCardSetData(const ECardSetType SetType) : SetType(SetType)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Set Data")
	FString SetName{};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Set Data")
	FString PackName{};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Set Data")
	ECardSetType SetType{ECardSetType::Hero};
};


UCLASS()
class CARDDATA_API UHeroIdentityCardSetData : public UCardSetData
{
	GENERATED_BODY()

public:
	UHeroIdentityCardSetData() : UCardSetData(ECardSetType::Hero)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Cards")
	TSoftObjectPtr<UHeroIdentityCardData> IdentityData;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Cards")
	TSoftObjectPtr<UHeroObligationCardData> ObligationData;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Cards")
	TArray<TSoftObjectPtr<UHeroPackCard>> HeroSetCardData;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Cards")
	TArray<TSoftObjectPtr<UNemesisCardData>> HeroNemesisCardData;
};

UCLASS()
class CARDDATA_API UAspectCardSetData : public UCardSetData
{
	GENERATED_BODY()

public:
	UAspectCardSetData() : UCardSetData(ECardSetType::Aspect)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Cards")
	TArray<TSoftObjectPtr<UHeroPackCard>> AspectSetCardData;
};

UCLASS()
class CARDDATA_API UBasicCardSetData : public UCardSetData
{
	GENERATED_BODY()

public:
	UBasicCardSetData() : UCardSetData(ECardSetType::Basic)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Cards")
	TArray<TSoftObjectPtr<UHeroPackCard>> BasicSetCardData;
};

UCLASS(Abstract)
class UHeroCardDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UHeroCardDataAsset() = default;
	explicit UHeroCardDataAsset(const bool IsUnique, const EHeroCardType Type) : IsUnique(IsUnique), Type(Type)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Card Data")
	bool IsUnique{false};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Card Data")
	FName HeroCardCode{};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Card Data")
	FString SetName{};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Card Data")
	FString PackName{};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Card Data")
	EHeroCardType Type{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Text")
	FString Name{};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Text")
	FString Text{};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Text", meta=(DisplayAfter="Text"))
	FString FlavorText{};
};

UCLASS()
class UHeroIdentityCardData : public UHeroCardDataAsset
{
	GENERATED_BODY()

public:
	UHeroIdentityCardData() : UHeroCardDataAsset(true, EHeroCardType::Hero)
	{
	}	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	int HandSize{0};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	int Health{0};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	int Attack{0};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	int Defense{0};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	int Thwart{0};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Text")
	TArray<FString> Traits;
};

UCLASS()
class UHeroAlterEgoCardData : public UHeroCardDataAsset
{
	GENERATED_BODY()

public:
	UHeroAlterEgoCardData() : UHeroCardDataAsset(true, EHeroCardType::AlterEgo)
	{
	}
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	int Recover{0};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	int HandSize{0};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	int Health{0};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Text")
	TArray<FString> Traits;
};

UCLASS()
class UHeroObligationCardData : public UHeroCardDataAsset
{
	GENERATED_BODY()

public:
	UHeroObligationCardData() : UHeroCardDataAsset(true, EHeroCardType::Obligation)
	{
	}
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	int Boost{0};
};

UCLASS()
class UHeroPackCard : public UHeroCardDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Card Data", meta=(ClampMin=1))
	int Quantity{1};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Card Data", meta=(ClampMin=1, ClampMax=3, EditCondition="!IsUnique"))	
	int DeckLimit{3};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Text", meta=(DisplayAfter="Name"))
	FString SubName{};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Text")
	TArray<FString> Traits;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	int Cost{0};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	int Health{0};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	int Attack{0};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	int AttackCost{0};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	int Thwart{0};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	int ThwartCost{0};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	TArray<FResourceCost> ResourceCost;
};

UCLASS()
class UNemesisCardData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Card Data")
	bool IsUnique{false};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Card Data")
	int Quantity{1};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Card Data")
	FName CardCode{};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Card Data")
	FString SetName{};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Card Data")
	FString PackName{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	int Health{0};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	int Boost{0};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	int BaseThreat{0};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	bool BaseFixed{false};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	int Scheme{0};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	int Attack{0};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	int SchemeHazard{0};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	int SchemeCrisis{0};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats")
	int SchemeAcceleration{0};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Text")
	FString Name{};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Text")
	FString Text{};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Text")
	FString FlavorText{};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Text")
	FString BoostText{};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Text")
	FString AttackText{};
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Text")
	TArray<FString> Traits;
};
