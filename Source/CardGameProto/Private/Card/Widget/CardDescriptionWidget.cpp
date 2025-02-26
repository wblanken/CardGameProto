// Fill out your copyright notice in the Description page of Project Settings.


#include "Card/Widget/CardDescriptionWidget.h"
#include "Components/TextBlock.h"
#include "Components/RichTextBlock.h"

void UCardDescriptionWidget::SetTraits(const FString& traits)
{
	TraitsTextBlock->SetText(FText::FromString(traits));
}

void UCardDescriptionWidget::SetDescription(const FString& description)
{
	DescriptionTextBlock->SetText(FText::FromString(description));
}

void UCardDescriptionWidget::SetFlavor(const FString& flavor)
{
	FlavorTextBlock->SetText(FText::FromString(flavor));
}
