// Fill out your copyright notice in the Description page of Project Settings.


#include "Config/ApiSettingsWidget.h"

#include "PackData.h"
#include "Config/ApiSettings.h"
#include "Styling/DefaultStyleCache.h"

UApiSettingsWidget::UApiSettingsWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	ColPadding(FMargin(0.f, 0.f, 10.f, 0.f)),
	LabelStyle(UE::Slate::Private::FDefaultStyleCache::GetEditor().GetTextBlockStyle()),
	InputStyle(UE::Slate::Private::FDefaultStyleCache::GetEditor().GetEditableTextBoxStyle())	
{
	LabelStyle.SetFontSize(18);	
	InputStyle.TextStyle.SetFontSize(15);
}

bool UApiSettingsWidget::Initialize()
{
	if(!Super::Initialize()) return false;
	
	ApiSettings = NewObject<UApiSettings>();

	return true;
}

void UApiSettingsWidget::ReleaseSlateResources(bool bReleaseChildren)
{
	MyApiSettingsWidget.Reset();
	Super::ReleaseSlateResources(bReleaseChildren);
}

void UApiSettingsWidget::HandleOnPacksLoaded(const TArray<FPackData>& packData) const
{
	if(OnPacksLoaded.IsBound())
	{
		OnPacksLoaded.Broadcast(packData);
	}	
}

TSharedRef<SWidget> UApiSettingsWidget::RebuildWidget()
{	
	MyApiSettingsWidget = SNew(SApiSettingsWidget)
		.ApiSettings(ApiSettings)
		.LabelStyle(&LabelStyle)
		.InputStyle(&InputStyle)
		.ColPadding(ColPadding)
		.OnPacksLoaded(BIND_UOBJECT_DELEGATE(FSOnPacksLoadedEvent, HandleOnPacksLoaded));

	return MyApiSettingsWidget.ToSharedRef();
}
