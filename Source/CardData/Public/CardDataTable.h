#pragma once

#include "Enums/CardSetType.h"
#include "Enums/CardTypes.h"
#include "Enums/Factions.h"
#include "ResourceCost.h"

#include "CardDataTable.generated.h"

struct FDeckCard;
struct FSetCard;

USTRUCT(BlueprintType)
struct FBaseCardData : public FTableRowBase
{
	GENERATED_BODY()
	FBaseCardData() {};
	
	FBaseCardData(const FDeckCard& Other);		
	FBaseCardData(const FSetCard& Other);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Code {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name {};		
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName PackCode {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Position {-1};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Quantity {-1};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECardType CardType {0};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EFaction Faction {0};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName CardSetCode {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SetPosition {-1};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECardSetType CardSetType {ECardSetType::None};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DeckLimit {-1};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Health {-1};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool HealthPerHero {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Scheme {-1};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Attack {-1};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AttackCost {-1};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString AttackText {};	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Traits {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString RealTraits {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString FlavorText {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsUnique {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Hidden {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Permanent {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool DoubleSided {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ImageSrc {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Text {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString RealText {};
};

USTRUCT(BlueprintType)
struct CARDDATA_API FHeroCardData : public FBaseCardData
{
	GENERATED_BODY()

	FHeroCardData()	{};

	explicit FHeroCardData(const FBaseCardData& Other) : FBaseCardData(Other) {};
	explicit FHeroCardData(const FDeckCard& Other) : FBaseCardData(Other) {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName LinkedToCode {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int HandSize {-1};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Cost {-1};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SubName {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Defense {-1};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DefenseCost {-1};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Thwart {-1};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ThwartCost {-1};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Recover {-1};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int RecoverCost {-1};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FResourceCost> ResourceCosts;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> DuplicatedBy;	
};

USTRUCT(BlueprintType)
struct FEncounterCardData : public FBaseCardData
{
	GENERATED_BODY()

	 FEncounterCardData() {};

	explicit FEncounterCardData(const FBaseCardData& Other) : FBaseCardData(Other) {};
	explicit FEncounterCardData(const FDeckCard& Other) : FBaseCardData(Other) {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Stage {-1};	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int BaseThreat {-1};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool BaseThreatFixed {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int EscalationThreat {-1};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool EscalationThreatFixed {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Threat {-1};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ThreatFixed {false};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SchemeCrisis {-1};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SchemeHazard {-1};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString BackText {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString BackFlavor {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName BackImageSrc {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Boost {-1};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString BoostText {};
};
