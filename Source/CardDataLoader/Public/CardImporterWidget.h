// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "Interfaces/IHttpRequest.h"

#include "CardImporterWidget.generated.h"

struct FPackData;
struct FBaseCardData;
struct FEncounterCardData;
struct FHeroCardData;
class UApiSettingsWidget;
class UCheckBox;
class UDataTable;
class UDataTableFactory;
class UDetailsView;
class UEditorUtilityButton;
class UEditorUtilityComboBoxString;
class UEditorUtilityEditableTextBox;
class UEditorUtilityThrobber;
class UPackDataAsset;

/**
 * 
 */
UCLASS()
class CARDDATALOADER_API UCardImporterWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual bool Initialize() override;

	UFUNCTION(BlueprintCallable, Category="CardDataLoader")
	void GetPackCardData(const FName& packCode);

	UFUNCTION(BlueprintCallable)
	void BuildDataAssetsFromTables(const FName& packCode, const FName& setCode = "all");

	UFUNCTION(BlueprintCallable)
	void SetBusy(bool isBusy);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="CardData", meta=(DisplayPriority=0))
	UDataTable* PackDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="CardData", meta=(DisplayPriority=1))
	UDataTable* SetDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="CardData", meta=(DisplayPriority=2))
	UDataTable* HeroDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="CardData", meta=(DisplayPriority=3))
	UDataTable* EncounterDataTable;

protected:
	UFUNCTION()
	void OnLoadPackBtnClicked();
	UFUNCTION()
	void OnBuildDataAssetBtnClicked();

private:
	UFUNCTION()
	void HandleOnPacksLoaded(const TArray<FPackData>& PackDataArray);

	UFUNCTION()
	void OnPackBuildSelectorChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	TOptional<FBaseCardData> BuildBaseCard(const FJsonObject& cardData, const FName& packCode);
	FHeroCardData BuildHeroCard(FBaseCardData& baseCard, const FJsonObject& cardData);
	TOptional<FHeroCardData> BuildLinkedHeroCard(FJsonObject& cardData, const FName& packCode);
	FEncounterCardData BuildEncounterCard(const FBaseCardData& baseCard, const FJsonObject& cardData);
	void ProcessPackData(const FName& packCode, const TArray<TSharedPtr<FJsonValue>>& CardData);
	UDataTable* CreateDataTable(const FString& tableName, const UScriptStruct& rowType) const;
	void OnPackCardLoadResponseReceived(const FName& packCode, const FHttpRequestPtr& request, const FHttpResponsePtr& response, bool bWasSuccessful);
	bool PopulatePackCombobox(UEditorUtilityComboBoxString* comboBox);
	UFUNCTION(BlueprintCallable)
	void PopulateDTPackSelector();

	TMap<FString, FName> PackNameMap;

	UPROPERTY(EditDefaultsOnly, Category="DataAssets")
	FString dataDir = "/Game/Data";

	UPROPERTY(EditDefaultsOnly, Category="DataAssets")
	FString tableDataDir = FPaths::Combine(dataDir, "Tables");

	UPROPERTY(EditDefaultsOnly, Category="DataAssets")
	FName packDataTableName = "DT_PackData";

	FName packDataTablePath = FName(FPaths::Combine(tableDataDir, packDataTableName.ToString()));

	UPROPERTY(EditDefaultsOnly, Category="DataAssets")
	FName setDataTableName = "DT_SetData";

	FName setDataTablePath = FName(FPaths::Combine(tableDataDir, setDataTableName.ToString()));

	UPROPERTY(EditDefaultsOnly, Category="DataAssets")
	FName heroDataTableName = "DT_HeroData";

	FName heroDataTablePath = FName(FPaths::Combine(tableDataDir, heroDataTableName.ToString()));

	UPROPERTY(EditDefaultsOnly, Category="DataAssets")
	FName encounterDataTableName = "DT_EncounterData";

	FName encounterDataTablePath = FName(FPaths::Combine(tableDataDir, encounterDataTableName.ToString()));

	UPROPERTY(meta=(BindWidget))
	UApiSettingsWidget* ApiSettingsWidget;

	UPROPERTY(meta=(BindWidget))
	UEditorUtilityComboBoxString* PackSelector;

	UPROPERTY(meta=(BindWidget))
	UEditorUtilityButton* LoadPackBtn;

	UPROPERTY(meta=(BindWidget))
	UEditorUtilityComboBoxString* PackBuildSelector;

	UPROPERTY(meta=(BindWidget))
	UEditorUtilityComboBoxString* SetBuildSelector;

	UPROPERTY(meta=(BindWidget))
	UEditorUtilityButton* BuildDataAssetsBtn;

	UPROPERTY(meta=(BindWidget))
	UEditorUtilityThrobber* LoadingIndicator;

	UPROPERTY(meta=(BindWidget))
	UDetailsView* PackDataView;
};
