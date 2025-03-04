// Fill out your copyright notice in the Description page of Project Settings.


#include "Card/Widget/CardAbilityWidget.h"

#include "Components/TextBlock.h"
#include "Components/Border.h"

void UCardAbilityWidget::SetValue(const int value)
{
	ValueText->SetText(FText::AsNumber(value));
}

void UCardAbilityWidget::SetText(const FText& Text)
{
	SkillAbbrText->SetText(Text);
}

void UCardAbilityWidget::SetColor(const FColor& Color)
{
	BackgroundBorder->SetBrushColor(Color);
}
