﻿// Copyright Will Blankenship 2024


#include "CardGameProtoAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "CardGameGameplayTags.h"

UCardGameProtoAssetManager& UCardGameProtoAssetManager::Get()
{
	check(GEngine);
	
	auto auraAssetManager = Cast<UCardGameProtoAssetManager>(GEngine->AssetManager);
	return *auraAssetManager;
}

void UCardGameProtoAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FCardGameGameplayTags::InitializeNativeGameplayTags();
	// This is required to use Target Data!
	UAbilitySystemGlobals::Get().InitGlobalData();
}
