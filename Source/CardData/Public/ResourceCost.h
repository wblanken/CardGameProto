#pragma once
#include "Enums/Resource.h"

#include "ResourceCost.generated.h"

USTRUCT(BlueprintType)
struct FResourceCost
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EResource> Resource {Wild};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin=0))
	int Cost {0};
};
