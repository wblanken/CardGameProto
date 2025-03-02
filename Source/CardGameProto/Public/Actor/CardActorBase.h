// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "CardActorBase.generated.h"

class UCardNameWidget;
class UStaticMeshComponent;
class UTextRenderComponent;

UCLASS(Abstract)
class CARDGAMEPROTO_API ACardActorBase : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACardActorBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> CardMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card UI")
	TObjectPtr<UWidgetComponent> NameWidget;
	
	UPROPERTY(EditAnywhere, Category = "Card UI")
	TObjectPtr<UWidgetComponent> DescriptionWidget;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Card Data", meta=(RowType="BaseCardData"))
	FDataTableRowHandle CardData;
};
