// Copyright Will Blankenship 2024


#include "Card/Widget/CardWidgetController.h"

void UCardWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& params)
{
	AbilitySystemComponent = params.AbilitySystemComponent;
	AttributeSet = params.AttributeSet;
}

void UCardWidgetController::BroadcastInitialValues()
{}

void UCardWidgetController::BindCallbacksToDependencies()
{}
