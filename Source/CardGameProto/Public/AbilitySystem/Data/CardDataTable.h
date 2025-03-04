// Copyright Will Blankenship 2024

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CardDataTable.generated.h"

/**
 * 
 */
USTRUCT()
struct FCardTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FName Code;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FName Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool Unique {false};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FName> Traits;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText Description;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText Flavor;
};

USTRUCT(BlueprintType)
struct FHeroCardTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FName HeroCode;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FName HeroName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FName> HeroTraits;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText HeroDescription;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText HeroFlavor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 HeroHandSize;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FName AlterEgoCode;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FName AlterEgoName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FName> AlterEgoTraits;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText AlterEgoDescription;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText AlterEgoFlavor;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 AlterEgoHandSize;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 HitPoints;	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 Attack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 Thwart;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 Defense;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 Recover;
};

