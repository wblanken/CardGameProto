// Copyright Will Blankenship 2024

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SetData.generated.h"

UENUM(BlueprintType)
enum class ECardSetType : uint8
{
	None,
	Basic,
	Aspect,
	Hero,
	Expert,
	Modular,
	Nemesis,
	Standard,
	Villain,
	Pool
};

UCLASS()
class CARDGAMEPROTO_API USetData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category="Card Set Data")
	FName SetName;

	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category="Card Set Data")
	FName SetCode;
	
	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category="Card Set Data")
	ECardSetType SetType;

	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category="Card Set Data")
	TArray<FDataTableRowHandle> SetCards;
};
