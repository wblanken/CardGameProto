#pragma once

#include "Card.h"

#include "ScenarioDeck.generated.h"

USTRUCT(BlueprintType)
struct FScenarioDeck : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ModularSet {false};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ExpertMode {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSet<FDeckCard> DeckCards;
};