// Copyright Will Blankenship 2024


#include "Card/Widget/CardGameWidget.h"

void UCardGameWidget::SetWidgetController(UObject* inWidgetController)
{
	WidgetController = inWidgetController;
	WidgetControllerSet();
}
