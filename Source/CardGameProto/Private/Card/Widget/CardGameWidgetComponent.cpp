// Copyright Will Blankenship 2024


#include "Card/Widget/CardGameWidgetComponent.h"


// Sets default values for this component's properties
UCardGameWidgetComponent::UCardGameWidgetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UCardGameWidgetComponent::SetWidgetController(UCardWidgetController* inWidgetController)
{
	WidgetController = inWidgetController;
	Cast<UCardGameWidget>(GetWidget())->SetWidgetController(WidgetController);
}


// Called when the game starts
void UCardGameWidgetComponent::BeginPlay()
{
	Super::BeginPlay();	
}