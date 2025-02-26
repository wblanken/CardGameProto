// Fill out your copyright notice in the Description page of Project Settings.


#include "Config/SApiSettingsWidget.h"

#include "CardDataLoader.h"
#include "JsonObjectConverter.h"
#include "PackData.h"
#include "SlateOptMacros.h"
#include "Config/ApiSettings.h"
#include "Widgets/Images/SThrobber.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Text/STextBlock.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

/**
 * Constructs and initializes the SApiSettingsWidget instance with the provided arguments.
 * Sets up UI components such as text labels, editable text boxes, and buttons in a grid layout,
 * binding the widgets to interact with the ApiSettings object.
 *
 * @param InArgs The arguments structure that contains initialization parameters like ApiSettings, LabelStyle,
 *               InputStyle, ColPadding, and event delegates such as OnPacksLoaded.
 */
void SApiSettingsWidget::Construct(const FArguments& InArgs)
{
	ApiSettings = InArgs._ApiSettings;
	checkf(ApiSettings.IsValid(), TEXT("ApiSettings is invlaid!"));

	LabelStyle = InArgs._LabelStyle;
	InputStyle = InArgs._InputStyle;

	const auto ColPadding = InArgs._ColPadding;	

	OnPacksLoaded = InArgs._OnPacksLoaded;
	
	ChildSlot
	.VAlign(VAlign_Fill)
	.HAlign(HAlign_Fill)
	[
		SNew(SGridPanel).FillColumn(1, 1.0f)
		+SGridPanel::Slot(0, 0).VAlign(VAlign_Fill).HAlign(HAlign_Fill).Padding(ColPadding)
		[
			SNew(STextBlock).Text(FText::FromString("DB Site:")).TextStyle(LabelStyle)
		]
		+SGridPanel::Slot(1, 0).VAlign(VAlign_Fill).HAlign(HAlign_Fill)
		[
			SNew(SEditableTextBox)
			.Style(InputStyle)
			.Text_UObject(ApiSettings.Get(), &UApiSettings::GetBaseUrl)			
			.OnTextChanged_UObject(ApiSettings.Get(), &UApiSettings::SetBaseUrl)
			.RevertTextOnEscape(true)
		]
		+SGridPanel::Slot(0, 1).VAlign(VAlign_Fill).HAlign(HAlign_Fill).Padding(ColPadding)
		[
			SNew(STextBlock).Text(FText::FromString("API Base:")).TextStyle(LabelStyle)
		]
		+SGridPanel::Slot(1, 1).VAlign(VAlign_Fill).HAlign(HAlign_Fill)
		[
			SNew(SEditableTextBox)
			.Style(InputStyle)
			.Text_UObject(ApiSettings.Get(), &UApiSettings::GetApiUrl)			
			.OnTextChanged_UObject(ApiSettings.Get(), &UApiSettings::SetApiUrl)
			.RevertTextOnEscape(true)
		]
		+SGridPanel::Slot(0, 2).VAlign(VAlign_Fill).HAlign(HAlign_Fill).Padding(ColPadding)
		[
			SNew(STextBlock).Text(FText::FromString("Set API:")).TextStyle(LabelStyle)
		]
		+SGridPanel::Slot(1, 2).VAlign(VAlign_Fill).HAlign(HAlign_Fill)
		[
			SNew(SEditableTextBox)
			.Style(InputStyle)
			.Text_UObject(ApiSettings.Get(), &UApiSettings::GetSetUrl)			
			.OnTextChanged_UObject(ApiSettings.Get(), &UApiSettings::SetSetUrl)
			.RevertTextOnEscape(true)
		]
		+SGridPanel::Slot(0, 3).VAlign(VAlign_Fill).HAlign(HAlign_Fill).Padding(ColPadding)
		[
			SNew(STextBlock).Text(FText::FromString("Packs API:")).TextStyle(LabelStyle)
		]
		+SGridPanel::Slot(1, 3).VAlign(VAlign_Fill).HAlign(HAlign_Fill)
		[
			SNew(SEditableTextBox)
			.Style(InputStyle)
			.Text_UObject(ApiSettings.Get(), &UApiSettings::GetPacksUrl)			
			.OnTextChanged_UObject(ApiSettings.Get(), &UApiSettings::SetPacksUrl)
			.RevertTextOnEscape(true)
		]
		+SGridPanel::Slot(0, 4).VAlign(VAlign_Fill).HAlign(HAlign_Fill).Padding(ColPadding)
		[
			SNew(STextBlock).Text(FText::FromString("Cards By Pack API:")).TextStyle(LabelStyle)
		]
		+SGridPanel::Slot(1, 4).VAlign(VAlign_Fill).HAlign(HAlign_Fill)
		[
			SNew(SEditableTextBox)
			.Style(InputStyle)
			.Text_UObject(ApiSettings.Get(), &UApiSettings::GetCardsUrl)			
			.OnTextChanged_UObject(ApiSettings.Get(), &UApiSettings::SetCardsUrl)
			.RevertTextOnEscape(true)
		]
		+SGridPanel::Slot(0, 5).VAlign(VAlign_Fill).HAlign(HAlign_Fill).Padding(ColPadding)
		[
			SNew(STextBlock).Text(FText::FromString("Single Card API:")).TextStyle(LabelStyle)
		]
		+SGridPanel::Slot(1, 5).VAlign(VAlign_Fill).HAlign(HAlign_Fill)
		[
			SNew(SEditableTextBox)
			.Style(InputStyle)
			.Text_UObject(ApiSettings.Get(), &UApiSettings::GetCardUrl)			
			.OnTextChanged_UObject(ApiSettings.Get(), &UApiSettings::SetCardUrl)
			.RevertTextOnEscape(true)
		]
		+SGridPanel::Slot(0, 6).VAlign(VAlign_Fill).HAlign(HAlign_Fill).Padding(ColPadding)
		[
			SNew(STextBlock).Text(FText::FromString("Card Images API:")).TextStyle(LabelStyle)
		]
		+SGridPanel::Slot(1, 6).VAlign(VAlign_Fill).HAlign(HAlign_Fill)
		[
			SNew(SEditableTextBox)
			.Style(InputStyle)
			.Text_UObject(ApiSettings.Get(), &UApiSettings::GetCardImageUrl)			
			.OnTextChanged_UObject(ApiSettings.Get(), &UApiSettings::SetCardImageUrl)
			.RevertTextOnEscape(true)
		]
		+SGridPanel::Slot(0, 7).VAlign(VAlign_Fill).HAlign(HAlign_Left).Padding(25.f)
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			[
				SAssignNew(UpdatePacksBtn, SButton)
				.Text(FText::FromString("Refresh Pack Data Table"))
				.OnClicked(this, &SApiSettingsWidget::OnUpdatePacksClick)
				.TextStyle(LabelStyle)
			]
			+SVerticalBox::Slot().HAlign(HAlign_Fill)
			[
				SAssignNew(LoadingIndicator, SThrobber)
				.IsEnabled(false)
				.Visibility(EVisibility::Collapsed)
			]
		]
	];
}

/**
 * Handles the click event for the "Update Packs" button.
 * Disables the button, shows a loading indicator, builds the URL for the API request,
 * sends a GET request to load packs, and logs the API request details.
 *
 * @return FReply::Handled to indicate the event has been handled.
 */
FReply SApiSettingsWidget::OnUpdatePacksClick()
{
	UpdatePacksBtn->SetEnabled(false);
	LoadingIndicator->SetEnabled(true);
	LoadingIndicator->SetVisibility(EVisibility::Visible);

	const auto packUrl = BuildUrl({ApiSettings->GetBaseUrl().ToString(),
		ApiSettings->GetApiUrl().ToString(),
		ApiSettings->GetPacksUrl().ToString()});

	UE_LOG(LogCardDataLoader, Display, TEXT("Loading packs from %s"), *packUrl);
	
	// Load packs from API
	FHttpRequestRef request = FHttpModule::Get().CreateRequest();
	request->OnProcessRequestComplete().BindRaw(this, &SApiSettingsWidget::OnPacksResponseReceived);
	request->SetURL(packUrl);
	request->SetVerb("GET");
	request->ProcessRequest();
	
	return FReply::Handled();	
}

/**
 * Validates the API settings by checking if the ApiSettings object is valid.
 * Logs an error if the ApiSettings object is null.
 *
 * @return True if the ApiSettings object is valid; false otherwise.
 */
bool SApiSettingsWidget::CheckApiSettingsValid() const
{
	if(!ApiSettings.IsValid())
	{
		UE_LOG(LogCardDataLoader, Error, TEXT("ApiSettings is null"));
		return false;
	}
	return true;
}

/**
 * Handles the response from the HTTP request to retrieve pack data from the API.
 * Updates the UI based on the success or failure of the request and processes the response data if successful.
 *
 * @param request The HTTP request sent to the API.
 * @param response The HTTP response received from the API.
 * @param bWasSuccessful A boolean indicating whether the HTTP request was successful.
 */
void SApiSettingsWidget::OnPacksResponseReceived(FHttpRequestPtr request, FHttpResponsePtr response,
                                                 bool bWasSuccessful) 
{
	UpdatePacksBtn->SetEnabled(true);
	LoadingIndicator->SetEnabled(false);
	LoadingIndicator->SetVisibility(EVisibility::Collapsed);

	if(bWasSuccessful && OnPacksLoaded.IsBound())
	{
		TArray<FPackData> packData;
		if(FJsonObjectConverter::JsonArrayStringToUStruct(response->GetContentAsString(), &packData))
		{
			OnPacksLoaded.Execute(packData);	
		}
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
