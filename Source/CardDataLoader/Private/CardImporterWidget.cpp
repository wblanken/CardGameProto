#include "CardImporterWidget.h"

#include "AssetToolsModule.h"
#include "Card.h"
#include "CardDataLoader.h"
#include "CardDataTable.h"
#include "EditorAssetLibrary.h"
#include "EditorUtilityWidgetComponents.h"
#include "PackData.h"
#include "SetData.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Components/DetailsView.h"
#include "Components/PanelWidget.h"
#include "Config/ApiSettings.h"
#include "Config/ApiSettingsWidget.h"
#include "DataAssets/CardSetData.h"
#include "Enums/Factions.h"
#include "Factories/DataTableFactory.h"

void UCardImporterWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

/**
 * Initialize the UCardImporterWidget, setting up UI elements, loading data tables, and binding event handlers.
 * @return true if the initialization is successful, false otherwise.
 */
bool UCardImporterWidget::Initialize()
{
	if (!Super::Initialize()) return false;

	if (PackDataView)
	{
		PackDataView->SetObject(this);
		PackDataView->CategoriesToShow.Add("CardData");		
	}

	if (PackDataTable == nullptr)
	{
		PackDataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *packDataTablePath.ToString()));
	}

	if (SetDataTable == nullptr)
	{
		SetDataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *setDataTablePath.ToString()));
	}

	if (HeroDataTable == nullptr)
	{
		HeroDataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *heroDataTablePath.ToString()));
	}

	if (EncounterDataTable == nullptr)
	{
		EncounterDataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *encounterDataTablePath.ToString()));
	}

	if (ApiSettingsWidget)
	{
		ApiSettingsWidget->OnPacksLoaded.RemoveDynamic(this, &UCardImporterWidget::HandleOnPacksLoaded);
		ApiSettingsWidget->OnPacksLoaded.AddDynamic(this, &UCardImporterWidget::HandleOnPacksLoaded);
	}

	if (PackBuildSelector)
	{
		PackBuildSelector->OnSelectionChanged.RemoveDynamic(this, &UCardImporterWidget::OnPackBuildSelectorChanged);
		PackBuildSelector->OnSelectionChanged.AddDynamic(this, &UCardImporterWidget::OnPackBuildSelectorChanged);

		PackBuildSelector->SetIsEnabled(false);
	}

	if (PackSelector && LoadPackBtn)
	{
		LoadPackBtn->OnClicked.RemoveDynamic(this, &UCardImporterWidget::OnLoadPackBtnClicked);
		LoadPackBtn->OnClicked.AddDynamic(this, &UCardImporterWidget::OnLoadPackBtnClicked);

		PackSelector->SetIsEnabled(false);
		LoadPackBtn->SetIsEnabled(false);

		PopulateDTPackSelector();
	}

	if (SetBuildSelector && BuildDataAssetsBtn)
	{
		BuildDataAssetsBtn->OnClicked.RemoveDynamic(this, &UCardImporterWidget::OnBuildDataAssetBtnClicked);
		BuildDataAssetsBtn->OnClicked.AddDynamic(this, &UCardImporterWidget::OnBuildDataAssetBtnClicked);

		SetBuildSelector->SetIsEnabled(false);
		BuildDataAssetsBtn->SetIsEnabled(false);
	}

	if (LoadingIndicator)
	{
		LoadingIndicator->SetIsEnabled(false);
		LoadingIndicator->SetVisibility(ESlateVisibility::Collapsed);
	}

	return true;
}

/**
 * Handles the OnClick event for the Load Pack button.
 * Verifies the existence of the PackSelector and PackDataTable objects, sets the widget to a busy state,
 * retrieves the selected pack code, and fetches card data for the selected pack.
 */
void UCardImporterWidget::OnLoadPackBtnClicked()
{
	verify(PackSelector);
	verify(PackDataTable);

	SetBusy(true);
	const auto selectedPackCode = PackNameMap[PackSelector->GetSelectedOption()];
	GetPackCardData(selectedPackCode);
}

/**
 * Handles the "Build Data Assets" button click event. Validates the Pack and Set selectors,
 * switches the widget to a busy state, retrieves the selected pack and set codes,
 * and initiates the process of building data assets from tables.
 */
void UCardImporterWidget::OnBuildDataAssetBtnClicked()
{
	verify(PackBuildSelector);
	verify(SetBuildSelector);

	SetBusy(true);
	const auto selectedPackCode = PackNameMap[PackBuildSelector->GetSelectedOption()];
	const auto selectedSetCode = FName(SetBuildSelector->GetSelectedOption());
	BuildDataAssetsFromTables(selectedPackCode, selectedSetCode);
}

/**
 * Handles the event when pack data is loaded. Updates or creates a data table asset
 * with the provided pack information and refreshes the pack selector UI.
 * @param PackDataArray Array of pack data containing the pack details to be processed and added to the data table.
 */
void UCardImporterWidget::HandleOnPacksLoaded(const TArray<FPackData>& PackDataArray)
{
	// The asset isn't assigned, lets create it
	if (PackDataTable == nullptr)
	{
		// Make sure the Data directory exists, create if not
		IPlatformFile& platformFile = FPlatformFileManager::Get().GetPlatformFile();
		const FString path = FPaths::Combine(FPaths::ProjectContentDir(), "Data");

		if (!platformFile.DirectoryExists(*path))
		{
			platformFile.CreateDirectory(*path);
		}

		PackDataTable = CreateDataTable(packDataTableName.ToString(), *FPackData::StaticStruct());

		if (PackDataTable == nullptr)
		{
			UE_LOG(LogCardDataLoader, Error, TEXT("Couldn't create PackData asset! %s/%s"), *dataDir, *packDataTableName.ToString());
			return;
		}
	}

	checkf(PackDataTable, TEXT("PackDataTable is null! Make sure you've loaded the pack data before processing!"));

	PackDataTable->EmptyTable();
	for (auto pack : PackDataArray)
	{
		PackDataTable->AddRow(pack.Code, pack);
	}

	PopulateDTPackSelector();
}

void UCardImporterWidget::OnPackBuildSelectorChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	SetBuildSelector->ClearOptions();
	SetBuildSelector->SetIsEnabled(false);
	BuildDataAssetsBtn->SetIsEnabled(false);

	if(!PackDataTable)
	{
		UE_LOG(LogCardDataLoader, Display, TEXT("PackData table not set, can't populate set selector."));
		return;
	}
	
	// Update the SetBuildSelector list to be sets from the selected pack.	
	if (!SetDataTable)
	{
		UE_LOG(LogCardDataLoader, Display, TEXT("SetData table not set, can't populate set selector."));
		return;
	}

	const auto packData = PackDataTable->FindRow<FPackData>(PackNameMap[SelectedItem], "UCardImporterWidget::OnPackBuildSelectorChanged", true);
	if (!packData || packData->CardSetCodes.IsEmpty())
	{
		UE_LOG(LogCardDataLoader, Warning, TEXT("PackData table doesn't contain needed data for pack: %s! Can't populate set selector."), *SelectedItem);
		return;
	}

	SetBuildSelector->AddOption("all");

	for (auto setCode : packData->CardSetCodes.Array())
	{
		SetBuildSelector->AddOption(setCode.ToString());
	}

	if (SetBuildSelector->GetOptionCount() > 0)
	{
		SetBuildSelector->SetIsEnabled(true);
		BuildDataAssetsBtn->SetIsEnabled(true);
	}
}

/**
 * Download all the cards for a given pack from the API. 
 * @param packCode data struct for the pack to download.
 */
void UCardImporterWidget::GetPackCardData(const FName& packCode)
{
	const auto& apiSettings = ApiSettingsWidget->GetApiSettings();

	const auto requestUrl = SApiSettingsWidget::BuildUrl({
		apiSettings.GetBaseUrl().ToString(),
		apiSettings.GetApiUrl().ToString(),
		apiSettings.GetCardsUrl().ToString(),
		packCode.ToString()
	});

	const auto request = FHttpModule::Get().CreateRequest();
	request->OnProcessRequestComplete().BindLambda(
		[this, packCode](const FHttpRequestPtr& request, const FHttpResponsePtr& response, bool wasSuccessful)
		{
			this->OnPackCardLoadResponseReceived(packCode, request, response, wasSuccessful);
		});
	request->SetURL(requestUrl);
	request->SetVerb("GET");
	request->ProcessRequest();
}

/**
 * Builds data assets from the specified pack and set codes by verifying the necessary data tables,
 * retrieving or creating the corresponding assets, and processing asset metadata.
 * @param packCode The identifier for the pack to be processed.
 * @param setCode The identifier for the set to be processed, or 'all' to process all sets in the given pack.
 */
void UCardImporterWidget::BuildDataAssetsFromTables(const FName& packCode, const FName& setCode)
{
	if (!ensureAlwaysMsgf(PackDataTable, TEXT("PackDataTable is null! Make sure you've loaded the pack data before processing!")))
	{
		return;
	}

	const auto packData = PackDataTable->FindRow<FPackData>(packCode, "UCardImporterWidget::BuildDataAssetsFromTables", false);
	if (!ensureAlwaysMsgf(packData, TEXT("Couldn't find pack data for %s! Make sure you've loaded all the pack's data before processing.")))
	{
		return;
	}

	if (!ensureAlwaysMsgf(SetDataTable, TEXT("SetDataTable is null! Make sure you've loaded the set data before processing!")))
	{
		return;
	}

	TArray<FName> setCodes;
	if (setCode.IsEqual("all", ENameCase::IgnoreCase))
	{
		setCodes = packData->CardSetCodes.Array();
		if (!ensureAlwaysMsgf(setCodes.IsEmpty(), TEXT("Couldn't find set data for pack %s! Make sure you've loaded all the pack's data before processing.")))
		{
			return;
		}
	}
	else
	{
		setCodes.Add(setCode);
	}

	// TODO - Get or create the Pack Data Asset - UPackDataAsset
	const IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();
	FARFilter Filter;
	Filter.PackagePaths.Add(FName(dataDir));
	Filter.bRecursivePaths = true;

	Filter.ClassPaths.Add(UPackDataAsset::StaticClass()->GetClassPathName());
	Filter.bRecursiveClasses = false;

	UPackDataAsset packDataAsset;
	{
		TArray<FAssetData> AssetData;
		AssetRegistry.GetAssets(Filter, AssetData);

		for (auto asset : AssetData)
		{
			UE_LOG(LogCardDataLoader, Display, TEXT("Found asset: %s"), *asset.AssetName.ToString());
		}
	}

	for (auto code : setCodes)
	{
		// TODO - Get or create the Set Data Asset - UCardSetData derived type
		// TODO - Get or create the Card Data Assets - UHeroCardDataAsset derived type
	}

	if (!ensureAlwaysMsgf(HeroDataTable, TEXT("SetDataTable is null! Make sure you've loaded the set data before processing!")))
	{
		return;
	}

	if (!ensureAlwaysMsgf(EncounterDataTable, TEXT("SetDataTable is null! Make sure you've loaded the set data before processing!")))
	{
		return;
	}
}

/**
 * Toggles the busy state of the UCardImporterWidget UI to indicate an ongoing process.
 * Disables or enables interactive elements and updates the visibility of the loading indicator.
 *
 * @param isBusy Set to true to indicate a busy state (disables interactive elements and shows the loading indicator),
 *               or false for an idle state (enables interactive elements and hides the loading indicator).
 */
void UCardImporterWidget::SetBusy(bool isBusy)
{
	PackSelector->SetIsEnabled(!isBusy);
	PackBuildSelector->SetIsEnabled(!isBusy);
	SetBuildSelector->SetIsEnabled(!isBusy);
	LoadPackBtn->SetIsEnabled(!isBusy);
	BuildDataAssetsBtn->SetIsEnabled(!isBusy);
	LoadingIndicator->SetIsEnabled(isBusy);
	LoadingIndicator->SetVisibility(isBusy ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

/**
 * Handles the HTTP response received after attempting to load a pack's card data.
 * Deserializes the response into JSON format and processes the card data if the operation is successful.
 * If unsuccessful, logs an error and exits the function.
 *
 * @param packCode The unique identifier for the card pack being loaded.
 * @param request The HTTP request object used to fetch the card pack data.
 * @param response The HTTP response object containing the card pack data or error details.
 * @param wasSuccessful A boolean flag indicating whether the request was successful.
 */
void UCardImporterWidget::OnPackCardLoadResponseReceived(const FName& packCode, const FHttpRequestPtr& request, const FHttpResponsePtr& response, bool wasSuccessful)
{
	if (!wasSuccessful)
	{
		UE_LOG(LogCardDataLoader, Error, TEXT("Error loading pack: %s"), *request->GetURL());
		return;
	}

	// Get the card data as Json Objects 
	const auto msgBody = response->GetContentAsString();

	const auto JSONReader = TJsonReaderFactory<>::Create(*msgBody);
	if (TSharedPtr<FJsonValue> cards; FJsonSerializer::Deserialize(JSONReader, cards) && cards.IsValid())
	{
		ProcessPackData(packCode, cards->AsArray());
	}
	else
	{
		SetBusy(false);
	}
}

/**
 * Populates the given combo box with pack options from the PackDataTable and stores mapping of pack names to their codes.
 * @param comboBox A pointer to the combo box that will be populated with pack options.
 * @return true if the combo box was successfully populated, false if the combo box pointer is null or an error occurred.
 */
bool UCardImporterWidget::PopulatePackCombobox(UEditorUtilityComboBoxString* comboBox)
{
	if (comboBox)
	{
		comboBox->ClearOptions();
		PackNameMap.Empty();

		for (const auto rowName : PackDataTable->GetRowNames())
		{
			if (const auto packData = PackDataTable->FindRow<FPackData>(
				rowName, "UCardImporterWidget::PopulatePackComboBox"))
			{
				comboBox->AddOption(packData->Name);
				PackNameMap.Add(packData->Name, packData->Code);
			}
		}
		comboBox->SetSelectedIndex(0);
		return true;
	}

	return false;
}

/**
 * Populates the data table pack selector widget, enabling or disabling related UI elements
 * based on the state of the PackDataTable.
 * If PackDataTable is valid, it populates the PackSelector and PackBuildSelector comboboxes, enabling them
 * and the LoadPack button. If PackDataTable is null, the comboboxes and the button are disabled,
 * and their options are cleared.
 */
void UCardImporterWidget::PopulateDTPackSelector()
{
	if (PackDataTable != nullptr)
	{
		if (PopulatePackCombobox(PackSelector))
		{
			PackSelector->SetIsEnabled(true);
			LoadPackBtn->SetIsEnabled(true);
			if (PopulatePackCombobox(PackBuildSelector))
			{
				PackBuildSelector->SetIsEnabled(true);
			}
		}
	}
	else
	{
		if(PackSelector)
		{
			PackSelector->SetIsEnabled(false);
			PackSelector->ClearOptions();
		}
		if(LoadPackBtn)
		{
			LoadPackBtn->SetIsEnabled(false);
		}
		if(PackBuildSelector)
		{
			PackBuildSelector->SetIsEnabled(false);
			PackBuildSelector->ClearOptions();
		}
	}
}


/**
 * Run tasks to create the set lists, hero card lists, and encounter card lists.
 * @param packCode Code of the Pack being loaded
 * @param cardData JsonValues for the cards
 */
void UCardImporterWidget::ProcessPackData(const FName& packCode, const TArray<TSharedPtr<FJsonValue>>& cardData)
{
	if (!ensureAlwaysMsgf(PackDataTable, TEXT("PackDataTable is null! Make sure you've loaded the pack data before processing!")))
	{
		return;
	}

	if (SetDataTable == nullptr)
	{
		SetDataTable = CreateDataTable(setDataTableName.ToString(), *FCardSet::StaticStruct());
		if (!ensureAlwaysMsgf(SetDataTable, TEXT("Failed to create SetDataTable, cannot continue processing cards!")))
		{
			return;
		}
	}

	if (HeroDataTable == nullptr)
	{
		HeroDataTable = CreateDataTable(heroDataTableName.ToString(), *FHeroCardData::StaticStruct());
		if (!ensureAlwaysMsgf(HeroDataTable, TEXT("Failed to create HeroDataTable, cannot continue processing cards!")))
		{
			return;
		}
	}

	if (EncounterDataTable == nullptr)
	{
		EncounterDataTable = CreateDataTable(encounterDataTableName.ToString(), *FEncounterCardData::StaticStruct());
		if (!ensureAlwaysMsgf(EncounterDataTable, TEXT("Failed to create EncounterDataTable, cannot continue processing cards!")))
		{
			return;
		}
	}

	TMap<FName, FCardSet> packSets;
	TSet<FName> packHeroCards;
	TSet<FName> packEncounterCards;

	for (const auto cardValue : cardData)
	{
		auto cardObj = *cardValue->AsObject();

		auto card = BuildBaseCard(cardObj, packCode);
		if (!card)
		{
			continue;
		}
		TOptional<FCardSet> set;
		if (!card->CardSetCode.IsNone())
		{
			if (packSets.Contains(card->CardSetCode))
			{
				set = packSets[card->CardSetCode];
			}
			else
			{
				set = FCardSet();
				set->CardSetCode = card->CardSetCode;
				if (!cardObj.TryGetStringField(TEXT("card_set_name"), set->CardSetName))
				{
					set->CardSetName = card->CardSetCode.ToString();
					set->CardSetName[0] = toupper(set->CardSetName[0]);
				}
				set->PackCode = packCode;
			}

			// Aspect and basic cards already have this data set during earlier processing.
			if (card->CardSetType == ECardSetType::None)
			{
				const auto setTypeString = cardObj.GetStringField(TEXT("card_set_type_name_code"));
				auto setTypeEnum = StaticEnum<ECardSetType>()->GetValueByNameString(setTypeString);

				if (setTypeEnum == -1)
				{
					UE_LOG(LogCardDataLoader, Error, TEXT("Invalid Set Type: %s. Can't process card %s further, skipping!"),
					       *setTypeString, *card->Name);
					continue;
				}
				card->CardSetType = static_cast<ECardSetType>(setTypeEnum);
				cardObj.TryGetNumberField(TEXT("set_position"), card->SetPosition);
			}
		}

		// Figure out if this is a Hero or Encounter card
		switch (card->Faction)
		{
		case EFaction::Aggression:
		case EFaction::Justice:
		case EFaction::Leadership:
		case EFaction::Protection:
		case EFaction::Basic:
		case EFaction::Hero:
			{
				auto heroCard = BuildHeroCard(*card, cardObj);
				packHeroCards.Add(heroCard.Code);
				if (set)
				{
					set->SetHeroCards.Add(FSetCard(heroCard));
				}
				HeroDataTable->AddRow(heroCard.Code, heroCard);

				// Build linked card data when there is one
				if (!heroCard.LinkedToCode.IsNone())
				{
					if (auto linkedHeroCard = BuildLinkedHeroCard(cardObj, packCode))
					{
						packHeroCards.Add(linkedHeroCard.GetValue().Code);
						if (set)
						{
							set->SetHeroCards.Add(FSetCard(linkedHeroCard.GetValue()));
						}
						HeroDataTable->AddRow(linkedHeroCard->Code, linkedHeroCard.GetValue());
					}
				}
				break;
			}
		case EFaction::Encounter:
			{
				auto encounterCard = BuildEncounterCard(*card, cardObj);

				packEncounterCards.Add(encounterCard.Code);
				if (set)
				{
					set->SetEncounterCards.Add(FSetCard(encounterCard));
				}
				EncounterDataTable->AddRow(encounterCard.Code, encounterCard);
				break;
			}
		case EFaction::Campaign:
			// Not used yet
			break;
		default:
			checkf(false, TEXT("Invalid faction %s"), card->Faction);
			break;
		}

		if (set)
		{
			packSets.Add(card->CardSetCode, *set);
		}
	}

	auto packData = FPackData(*PackDataTable->FindRow<FPackData>(packCode, "UCardImporterWidget::ProcessPackData", true));
	packData.CardSetCodes.Empty();
	packData.HeroCardCodes = packHeroCards;
	packData.EncounterCardCodes = packEncounterCards;

	TArray<FName> aspectDecks = {"aggression", "justice", "leadership", "protection", "basic"};

	for (auto cardSet : packSets)
	{
		packData.CardSetCodes.Add(cardSet.Key);

		if (aspectDecks.Find(cardSet.Key) != INDEX_NONE)
		{
			cardSet.Value.SetHeroCards.Sort([](const FSetCard& lhs, const FSetCard& rhs)
			{
				return lhs.SetPosition < rhs.SetPosition;
			});
			cardSet.Value.SetEncounterCards.Sort([](const FSetCard& lhs, const FSetCard& rhs)
			{
				return lhs.SetPosition < rhs.SetPosition;
			});

			auto i = 1;
			for (auto setCard : cardSet.Value.SetHeroCards)
			{
				setCard.SetPosition = i;
				++i;
			}
		}
		// Sort set cards by position.		
		SetDataTable->AddRow(cardSet.Key, cardSet.Value);
	}

	PackDataTable->AddRow(packCode, packData);

	SetBusy(false);
}

/**
 * Builds a base card object from a JSON-defined card data structure and associates it with a specific pack code.
 * @param cardData JSON object containing the card data, including attributes like name, type, traits, etc.
 * @param packCode Identifier for the card's associated pack.
 * @return An optional FBaseCardData. If the card data is invalid (e.g., contains invalid faction or type information), returns NullOpt.
 */
TOptional<FBaseCardData> UCardImporterWidget::BuildBaseCard(const FJsonObject& cardData, const FName& packCode)
{
	FBaseCardData card;
	card.Name = cardData.GetStringField(TEXT("name"));
	card.Code = FName(cardData.GetStringField(TEXT("code")));

	UE_LOG(LogCardDataLoader, Display, TEXT("Processing Card: %s - %s"), *card.Name, *card.Code.ToString());

	cardData.TryGetNumberField(TEXT("quantity"), card.Quantity);
	card.PackCode = packCode;
	cardData.TryGetNumberField(TEXT("position"), card.Position);
	cardData.TryGetNumberField(TEXT("quantity"), card.Quantity);
	cardData.TryGetNumberField(TEXT("deck_limit"), card.DeckLimit);
	cardData.TryGetNumberField(TEXT("health"), card.Health);
	card.HealthPerHero = cardData.GetBoolField(TEXT("health_per_hero"));
	cardData.TryGetNumberField(TEXT("scheme"), card.Scheme);
	cardData.TryGetNumberField(TEXT("attack"), card.Attack);
	cardData.TryGetNumberField(TEXT("attack_cost"), card.AttackCost);
	cardData.TryGetStringField(TEXT("attack_text"), card.AttackText);
	cardData.TryGetStringField(TEXT("traits"), card.Traits);
	cardData.TryGetStringField(TEXT("real_traits"), card.RealTraits);
	cardData.TryGetStringField(TEXT("flavor"), card.FlavorText);
	card.IsUnique = cardData.GetBoolField(TEXT("is_unique"));
	card.Hidden = cardData.GetBoolField(TEXT("hidden"));
	card.Permanent = cardData.GetBoolField(TEXT("permanent"));
	card.DoubleSided = cardData.GetBoolField(TEXT("double_sided"));

	FString cardImageSrc;
	if (cardData.TryGetStringField(TEXT("imagesrc"), cardImageSrc))
	{
		card.ImageSrc = FName(cardImageSrc);
	}

	// TODO Parse out the text into a format we can use with our rich text box.
	cardData.TryGetStringField(TEXT("text"), card.Text);
	cardData.TryGetStringField(TEXT("real_text"), card.RealText);

	const auto cardFaction = StaticEnum<EFaction>()->GetValueByNameString(cardData.GetStringField(TEXT("faction_name")));
	if (cardFaction == -1)
	{
		UE_LOG(LogCardDataLoader, Error, TEXT("Invalid card faction, can't process card %s further, skipping!"), *card.Name);
		return NullOpt;
	}

	card.Faction = static_cast<EFaction>(cardFaction);

	FString cardSetCode;
	if (cardData.TryGetStringField(TEXT("card_set_code"), cardSetCode))
	{
		// Merge nemesis sets into hero sets
		cardSetCode.RemoveFromEnd("_nemesis");
		card.CardSetCode = FName(cardSetCode);
	}
	else
	{
		// Check for aspect set
		switch (card.Faction)
		{
		case EFaction::Aggression:
			card.CardSetCode = FName("aggression");
			card.CardSetType = ECardSetType::Aspect;
			card.SetPosition = card.Position; // We'll sort the set by this later.
			break;
		case EFaction::Justice:
			card.CardSetCode = FName("justice");
			card.CardSetType = ECardSetType::Aspect;
			card.SetPosition = card.Position;
			break;
		case EFaction::Leadership:
			card.CardSetCode = FName("leadership");
			card.CardSetType = ECardSetType::Aspect;
			card.SetPosition = card.Position;
			break;
		case EFaction::Protection:
			card.CardSetCode = FName("protection");
			card.CardSetType = ECardSetType::Aspect;
			card.SetPosition = card.Position;
			break;
		case EFaction::Basic:
			card.CardSetCode = FName("basic");
			card.CardSetType = ECardSetType::Basic;
			card.SetPosition = card.Position;
			break;
		default:
			break;
		}
	}

	auto typeString = cardData.GetStringField(TEXT("type_name"));
	typeString.ReplaceCharInline('-', ' ');
	typeString.RemoveSpacesInline();
	const auto cardType = StaticEnum<ECardType>()->GetValueByNameString(typeString);
	if (cardType == -1)
	{
		UE_LOG(LogCardDataLoader, Error, TEXT("Invalid card type %s, can't process card %s further, skipping!"), *typeString, *card.Name);
		return NullOpt;
	}

	card.CardType = static_cast<ECardType>(cardType);

	return card;
}

/**
 * Constructs a hero card instance by populating the FHeroCardData structure with data
 * from a given base card and JSON object.
 *
 * The function initializes a hero card based on the provided base card data and updates
 * its properties by extracting values from the JSON object. These include various gameplay
 * attributes such as cost, hand size, defense, etc. Additionally, it handles complex relationships,
 * like linked cards or duplicate lists, and assigns related resource costs.
 *
 * @param baseCard The base card data from which the hero card is derived.
 * @param cardData A JSON object containing the additional data fields for the hero card.
 * @return A fully constructed FHeroCardData instance populated with the provided data.
 */
FHeroCardData UCardImporterWidget::BuildHeroCard(const FBaseCardData& baseCard, const FJsonObject& cardData)
{
	auto heroCard = FHeroCardData(baseCard);

	FString linkedToCode;
	if (cardData.TryGetStringField(TEXT("linked_to_code"), linkedToCode))
	{
		heroCard.LinkedToCode = FName(linkedToCode);
		heroCard.DoubleSided = true; // For some reason linked cards don't count as double-sided in the API.
	}

	cardData.TryGetNumberField(TEXT("hand_size"), heroCard.HandSize);
	cardData.TryGetNumberField(TEXT("cost"), heroCard.Cost);
	cardData.TryGetStringField(TEXT("subname"), heroCard.SubName);
	cardData.TryGetNumberField(TEXT("defense"), heroCard.Defense);
	cardData.TryGetNumberField(TEXT("defense_cost"), heroCard.DefenseCost);
	cardData.TryGetNumberField(TEXT("recover"), heroCard.Recover);
	cardData.TryGetNumberField(TEXT("recover_cost"), heroCard.RecoverCost);
	cardData.TryGetNumberField(TEXT("thwart"), heroCard.Thwart);
	cardData.TryGetNumberField(TEXT("thwart_cost"), heroCard.ThwartCost);

	const TArray<TSharedPtr<FJsonValue>>* dupeList;
	if (cardData.TryGetArrayField(TEXT("duplicated_by"), dupeList))
	{
		for (const auto& dupe : *dupeList)
		{
			auto dupeCode = FName(dupe->AsString());
			heroCard.DuplicatedBy.Emplace(dupeCode);
		}
	}

	int energy;
	if (cardData.TryGetNumberField(TEXT("resource_energy"), energy))
	{
		auto energyCost = FResourceCost();
		energyCost.Resource = EResource::Energy;
		energyCost.Cost = energy;
		heroCard.ResourceCosts.Emplace(energyCost);
	}
	int physical;
	if (cardData.TryGetNumberField(TEXT("resource_physical"), physical))
	{
		auto physicalCost = FResourceCost();
		physicalCost.Resource = EResource::Physical;
		physicalCost.Cost = physical;
		heroCard.ResourceCosts.Emplace(physicalCost);
	}
	int mental;
	if (cardData.TryGetNumberField(TEXT("resource_mental"), mental))
	{
		auto mentalCost = FResourceCost();
		mentalCost.Resource = EResource::Mental;
		mentalCost.Cost = mental;
		heroCard.ResourceCosts.Emplace(mentalCost);
	}
	int wild;
	if (cardData.TryGetNumberField(TEXT("resource_wild"), wild))
	{
		auto wildCost = FResourceCost();
		wildCost.Resource = EResource::Wild;
		wildCost.Cost = wild;
		heroCard.ResourceCosts.Emplace(wildCost);
	}

	return heroCard;
}

/**
 * Build a linked hero card by extracting and processing the "linked_card" field from the given JSON object.
 * It constructs a base card from the linked card's data and then transforms it into a hero card using the main card data.
 * Logs an error and returns NullOpt if the "linked_card" field is missing or if the base card could not be built.
 *
 * @param cardData The JSON object containing card data, potentially including a "linked_card" field with its data.
 * @param packCode The code identifying the card pack to which the card belongs.
 * @return An optional FHeroCardData object representing the linked hero card if successfully constructed, or NullOpt otherwise.
 */
TOptional<FHeroCardData> UCardImporterWidget::BuildLinkedHeroCard(const FJsonObject& cardData, const FName& packCode)
{
	if (const TSharedPtr<FJsonObject>* linkedCard; cardData.TryGetObjectField(TEXT("linked_card"), linkedCard))
	{
		auto baseCard = BuildBaseCard(*linkedCard->Get(), packCode);
		if (baseCard.IsSet())
		{
			return BuildHeroCard(baseCard.GetValue(), cardData);
		}
	}

	UE_LOG(LogCardDataLoader, Error, TEXT("Couldn't load linked card object!"));
	return NullOpt;
}

/**
 * Builds an encounter card by populating an FEncounterCardData structure with data from a base card and JSON object.
 *
 * @param baseCard The base card data to initialize the encounter card with.
 * @param cardData The JSON object containing additional properties for populating the encounter card.
 * @return A fully populated FEncounterCardData instance with data from the provided base card and JSON object.
 */
FEncounterCardData UCardImporterWidget::BuildEncounterCard(const FBaseCardData& baseCard, const FJsonObject& cardData)
{
	auto encounterCard = FEncounterCardData(baseCard);

	cardData.TryGetNumberField(TEXT("stage"), encounterCard.Stage);
	cardData.TryGetNumberField(TEXT("stage"), encounterCard.BaseThreat);
	cardData.TryGetBoolField(TEXT("base_threat_fixed"), encounterCard.BaseThreatFixed);
	cardData.TryGetNumberField(TEXT("escalation_threat"), encounterCard.EscalationThreat);
	cardData.TryGetBoolField(TEXT("escalation_threat_fixed"), encounterCard.EscalationThreatFixed);
	cardData.TryGetNumberField(TEXT("threat"), encounterCard.Threat);
	cardData.TryGetBoolField(TEXT("threat_fixed"), encounterCard.ThreatFixed);
	cardData.TryGetNumberField(TEXT("scheme_crisis"), encounterCard.SchemeCrisis);
	cardData.TryGetNumberField(TEXT("scheme_hazard"), encounterCard.SchemeHazard);
	cardData.TryGetStringField(TEXT("back_text"), encounterCard.BackText);
	cardData.TryGetStringField(TEXT("back_flavor"), encounterCard.BackFlavor);
	FString cardBackImage;
	if (cardData.TryGetStringField(TEXT("back_flavor"), cardBackImage))
	{
		encounterCard.BackImageSrc = FName(cardBackImage);
	};
	cardData.TryGetNumberField(TEXT("boost"), encounterCard.Boost);
	cardData.TryGetStringField(TEXT("boost_text"), encounterCard.BoostText);

	return encounterCard;
}

UDataTable* UCardImporterWidget::CreateDataTable(const FString& tableName, const UScriptStruct& rowType) const
{
	const auto factory = NewObject<UDataTableFactory>();
	factory->Struct = rowType;

	// Make sure the Data directory exists, create if not
	if (!UEditorAssetLibrary::DoesDirectoryExist(tableDataDir))
	{
		UEditorAssetLibrary::MakeDirectory(tableDataDir);
	}

	// Create the asset
	IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();

	UE_LOG(LogCardDataLoader, Display, TEXT("No PackDataTable asset assigned, creating!"));

	const auto newAsset = AssetTools.CreateAsset(tableName, tableDataDir, UDataTable::StaticClass(), factory);

	if (newAsset == nullptr)
	{
		UE_LOG(LogCardDataLoader, Error, TEXT("Couldn't create asset: %s/%s"), *tableDataDir, *tableName);
		return nullptr;
	}

	UEditorAssetLibrary::SaveDirectory(tableDataDir);

	return Cast<UDataTable>(newAsset);
}
