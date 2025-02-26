// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardActorBase.h"
#include "HeroCard.generated.h"

UCLASS()
class CARDGAMEPROTO_API AHeroCard : public ACardActorBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHeroCard();
	
	UFUNCTION(BlueprintCallable)
	void SetIsAlterEgo(bool isAlterEgo);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card UI")
	TObjectPtr<UWidgetComponent> AlterEgoNameWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card UI")
	TObjectPtr<UWidgetComponent> AlterEgoDescriptionWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card UI")
	TObjectPtr<UWidgetComponent> ThwartWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card UI")
	TObjectPtr<UWidgetComponent> AttackWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card UI")
	TObjectPtr<UWidgetComponent> DefenseWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card UI")
	TObjectPtr<UWidgetComponent> RecoveryWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Card Data", meta=(RowType="HeroCardData"))
	FDataTableRowHandle AlterEgoData;

private:
	bool IsAlterEgo {true};
};
