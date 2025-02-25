#pragma once

#include "Card.h"
#include "Enums/Aspect.h"

#include "StarterDeck.generated.h"

USTRUCT(BlueprintType)
struct FStarterDeck : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName HeroSet;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAspect DeckAspect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDeckCard> DeckCards;
};