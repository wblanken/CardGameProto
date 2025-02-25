// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ApiSettings.generated.h"

/**
 * 
 */
UCLASS(Config=Editor, DefaultConfig, meta=(DisplayName="Card Data API Settings"))
class CARDDATALOADER_API UApiSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:		
	UFUNCTION(BlueprintCallable)
	FText GetBaseUrl() const { return BaseUrl; }
	UFUNCTION(BlueprintCallable)
	void SetBaseUrl(const FText& newValue) { BaseUrl = newValue; SaveConfig(CPF_Config, *GetDefaultConfigFilename()); }
	
	UFUNCTION(BlueprintCallable)
	FText GetApiUrl() const { return ApiUrl; }
	UFUNCTION(BlueprintCallable)
	void SetApiUrl(const FText& newValue) { ApiUrl = newValue; SaveConfig(CPF_Config, *GetDefaultConfigFilename()); }
	
	UFUNCTION(BlueprintCallable)
	FText GetCardImageUrl() const { return CardImageUrl; }
	UFUNCTION(BlueprintCallable)
	void SetCardImageUrl(const FText& newValue) { CardImageUrl = newValue; SaveConfig(CPF_Config, *GetDefaultConfigFilename()); }
	
	UFUNCTION(BlueprintCallable)
	FText GetCardsUrl() const { return CardsUrl; }
	UFUNCTION(BlueprintCallable)
	void SetCardsUrl(const FText& newValue) { CardsUrl = newValue; SaveConfig(CPF_Config, *GetDefaultConfigFilename()); }
	
	UFUNCTION(BlueprintCallable)
	FText GetCardUrl() const { return CardUrl; }
	UFUNCTION(BlueprintCallable)
	void SetCardUrl(const FText& newValue) { CardUrl = newValue; SaveConfig(CPF_Config, *GetDefaultConfigFilename()); }
	
	UFUNCTION(BlueprintCallable)
	FText GetPacksUrl() const { return PacksUrl; }
	UFUNCTION(BlueprintCallable)
	void SetPacksUrl(const FText& newValue) { PacksUrl = newValue; SaveConfig(CPF_Config, *GetDefaultConfigFilename()); }
	
	UFUNCTION(BlueprintCallable)
	FText GetSetUrl() const { return SetUrl; }	
	UFUNCTION(BlueprintCallable)
	void SetSetUrl(const FText& newValue) { SetUrl = newValue; SaveConfig(CPF_Config, *GetDefaultConfigFilename()); }

private:
	UPROPERTY(Config, EditAnywhere, Category="CardApiSettings")
	FText BaseUrl;
	UPROPERTY(Config, EditAnywhere, Category="CardApiSettings")
	FText ApiUrl;
	UPROPERTY(Config, EditAnywhere, Category="CardApiSettings")
	FText CardImageUrl;
	UPROPERTY(Config, EditAnywhere, Category="CardApiSettings")
	FText CardsUrl;
	UPROPERTY(Config, EditAnywhere, Category="CardApiSettings")
	FText CardUrl;
	UPROPERTY(Config, EditAnywhere, Category="CardApiSettings")
	FText PacksUrl;
	UPROPERTY(Config, EditAnywhere, Category="CardApiSettings")
	FText SetUrl;
	
};
