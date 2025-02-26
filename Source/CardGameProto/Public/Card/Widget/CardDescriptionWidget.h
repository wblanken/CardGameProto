// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CardDescriptionWidget.generated.h"

class URichTextBlock;
class UTextBlock;
/**
 * 
 */
UCLASS()
class CARDGAMEPROTO_API UCardDescriptionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:	
	UFUNCTION(BlueprintCallable)
	void SetTraits(const FString& traits);
	
	UFUNCTION(BlueprintCallable)
	void SetDescription(const FString& description);
	
	UFUNCTION(BlueprintCallable)
	void SetFlavor(const FString& flavor);

protected:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTextBlock> TraitsTextBlock;
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<URichTextBlock> DescriptionTextBlock;
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTextBlock> FlavorTextBlock;
};
