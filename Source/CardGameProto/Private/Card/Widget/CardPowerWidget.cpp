// Fill out your copyright notice in the Description page of Project Settings.


#include "Card/Widget/CardPowerWidget.h"

#include "Components/TextBlock.h"
#include "Components/Border.h"

void UCardPowerWidget::SetValue(const int value)
{
	ValueText->SetText(FText::AsNumber(value));
}

void UCardPowerWidget::SetText(const FText& Text)
{
	SkillAbbrText->SetText(Text);
}

void UCardPowerWidget::SetColor(const FColor& Color)
{
	BackgroundBorder->SetBrushColor(Color);
}
