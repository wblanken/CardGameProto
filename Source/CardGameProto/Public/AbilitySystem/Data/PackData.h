// Copyright Will Blankenship 2024

#pragma once

#include "CoreMinimal.h"
#include "SetData.h"
#include "Engine/DataAsset.h"
#include "PackData.generated.h"

UCLASS()
class CARDGAMEPROTO_API UPackData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category="Card Pack Data")
	FName PackName;

	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category="Card Pack Data")
	FName PackCode;
	
	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category="Card Pack Data")
	TArray<TObjectPtr<USetData>> Sets;
};
