#pragma once

#include "PackData.generated.h"

USTRUCT(BlueprintType)
struct FPackData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Code {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Position {-1};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Available {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Known {0};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Total {0};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Url {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Id {-1};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSet<FName> CardSetCodes;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSet<FName> HeroCardCodes;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSet<FName> EncounterCardCodes;
};