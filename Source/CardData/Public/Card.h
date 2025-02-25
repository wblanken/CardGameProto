#pragma once
#include "CardDataTable.h"

#include "Card.generated.h"

struct FSetCard;

USTRUCT(BlueprintType)
struct FDeckCard
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Code {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Quantity {-1};

	bool operator == (const FDeckCard& Other) const
	{
		return Code == Other.Code;
	}
};

FORCEINLINE uint32 GetTypeHash(const FDeckCard& Data)
{
	return FCrc::MemCrc32(&Data, sizeof(FDeckCard));
}

USTRUCT(BlueprintType)
struct CARDDATA_API FSetCard : public FDeckCard
{
	GENERATED_BODY()

	FSetCard() {};
	
	explicit FSetCard(const FDeckCard& Other)
		: FDeckCard(Other)
	{}

	explicit FSetCard(const FBaseCardData& Data)
		: FDeckCard(Data.Code, Data.Name, Data.Quantity)
		, SetPosition(Data.SetPosition)
		, CardSetType(Data.CardSetType)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SetPosition {-1};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECardSetType CardSetType {ECardSetType::None};
	
	bool operator == (const FSetCard& Other) const
	{
		return FDeckCard::operator==(Other);		
	}	
};

FORCEINLINE uint32 GetTypeHash(const FSetCard& Data)
{
	return FCrc::MemCrc32(&Data, sizeof(FSetCard));
}