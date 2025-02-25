#pragma once

#include "Card.h"
#include "Enums/CardSetType.h"

#include "SetData.generated.h"

USTRUCT(BlueprintType)
struct FCardSet : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName CardSetCode;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CardSetName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName PackCode;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSet<FSetCard> SetHeroCards;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSet<FSetCard> SetEncounterCards;

	bool operator == (const FCardSet& Other) const
	{
		return CardSetCode == Other.CardSetCode;
	}
};

FORCEINLINE uint32 GetTypeHash(const FCardSet& Data)
{
	return FCrc::MemCrc32(&Data, sizeof(FCardSet));
}