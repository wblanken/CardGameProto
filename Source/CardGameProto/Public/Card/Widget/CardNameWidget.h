// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CardNameWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class CARDGAMEPROTO_API UCardNameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetCardName(const FString& cardName);	
	UFUNCTION(BlueprintCallable)
	void SetIsUnique(bool isUnique);

protected:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTextBlock> UniqueTextBlock;
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTextBlock> NameTextBlock;
};
