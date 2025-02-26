// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CardPowerWidget.generated.h"

class UBorder;
class UTextBlock;
/**
 * 
 */
UCLASS()
class CARDGAMEPROTO_API UCardPowerWidget : public UUserWidget
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable)
	void SetValue(const int value);

	UFUNCTION(BlueprintCallable)
	void SetText(const FText& Text);

	UFUNCTION(BlueprintCallable)
	void SetColor(const FColor& Color);

protected:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTextBlock> ValueText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTextBlock> SkillAbbrText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UBorder> BackgroundBorder;
};
