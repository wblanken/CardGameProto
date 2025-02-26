// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Http.h"
#include "Widgets/SCompoundWidget.h"

struct FPackData;
class UApiSettings;

DECLARE_DELEGATE_OneParam(FSOnPacksLoadedEvent, const TArray<FPackData>&);

/**
 * @class SApiSettingsWidget
 * @brief Represents a settings widget for configuring API-related settings and preferences.
 *
 * This class encapsulates the GUI components and logic for handling the
 * presentation and interaction with API settings. It is designed to simplify
 * the configuration process and provides intuitive controls for the user.
 *
 * The widget may include fields for specifying API endpoints, authentication
 * details, and other relevant parameters needed for API integration.
 */
class SApiSettingsWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SApiSettingsWidget) {}
	
	SLATE_ARGUMENT(TWeakObjectPtr<UApiSettings>, ApiSettings)
	
	/** Padding between the box/border and the text widget inside (overrides Style) */
	SLATE_ATTRIBUTE(FMargin, ColPadding)

	SLATE_EVENT(FSOnPacksLoadedEvent, OnPacksLoaded)
	
	SLATE_STYLE_ARGUMENT(FTextBlockStyle, LabelStyle)
	SLATE_STYLE_ARGUMENT(FEditableTextBoxStyle, InputStyle)
	
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	static FString BuildUrl(TArray<FString> inputs)
	{
		FString url = inputs[0];
		for (auto i = 1; i < inputs.Num(); ++i)
		{
			url += "/" + inputs[i].TrimStartAndEnd().TrimChar('/');
		}
		return url;
	}
	
private:	
	TWeakObjectPtr<UApiSettings> ApiSettings;
	const FTextBlockStyle* LabelStyle{};
	const FEditableTextBoxStyle* InputStyle{};

	TSharedPtr<SButton> UpdatePacksBtn;
	TSharedPtr<SThrobber> LoadingIndicator;
	FReply OnUpdatePacksClick();
	FSOnPacksLoadedEvent OnPacksLoaded;
	
	bool CheckApiSettingsValid() const;

	void OnPacksResponseReceived(FHttpRequestPtr request, FHttpResponsePtr response, bool bWasSuccessful);
};
