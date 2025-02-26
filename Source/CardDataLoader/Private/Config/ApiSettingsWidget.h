// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "Config/SApiSettingsWidget.h"
#include "ApiSettingsWidget.generated.h"

struct FPackData;
class UApiSettingsWidgetStyle;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPacksLoadedEvent, const TArray<FPackData>&, PackDataArray);

/**
 * @class UApiSettingsWidget
 * @brief A widget class used for managing and displaying API settings.
 *
 * UApiSettingsWidget provides functionality to configure and manage
 * settings required for API interaction. The widget is designed to run
 * within the Unreal Engine editor and offers a customizable appearance
 * and style.
 *
 * It facilitates the use of dynamic events for notifying other classes
 * when API-related data are loaded.
 */
UCLASS()
class CARDDATALOADER_API UApiSettingsWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:
	UApiSettingsWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual bool Initialize() override;

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Appearance", meta=(DisplayName="First Column Padding"))
	FMargin ColPadding;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Style", meta=(DisplayName="LabelStyle", ShowOnlyInnerProperties))
	FTextBlockStyle LabelStyle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Style", meta=(DisplayName="InputStyle", ShowOnlyInnerProperties))
	FEditableTextBoxStyle InputStyle;

	UPROPERTY(BlueprintAssignable, Category="API|Event")
	FOnPacksLoadedEvent OnPacksLoaded;	

	UApiSettings& GetApiSettings() const { return *ApiSettings; }
	
	void HandleOnPacksLoaded(const TArray<FPackData>& packData) const;
	
protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;

	TSharedPtr<SApiSettingsWidget> MyApiSettingsWidget;
	
	UPROPERTY()
	UApiSettings* ApiSettings;
};
