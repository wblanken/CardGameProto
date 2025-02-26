// Fill out your copyright notice in the Description page of Project Settings.


#include "Card/Widget/CardNameWidget.h"
#include "Components/TextBlock.h"


void UCardNameWidget::SetCardName(const FString& cardName)
{
	NameTextBlock->SetText(FText::FromString(cardName));	
}

void UCardNameWidget::SetIsUnique(bool isUnique)
{
	UniqueTextBlock->SetVisibility(isUnique
		? ESlateVisibility::Visible
		: ESlateVisibility::Collapsed);
}
