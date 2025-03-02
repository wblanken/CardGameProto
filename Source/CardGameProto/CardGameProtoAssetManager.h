// Copyright Will Blankenship 2024

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "CardGameProtoAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class CARDGAMEPROTO_API UCardGameProtoAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UCardGameProtoAssetManager& Get();
protected:
	virtual void StartInitialLoading() override;
};
