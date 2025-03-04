// Copyright Will Blankenship 2024

#pragma once

#include "CoreMinimal.h"
#include "CardGameWidget.h"
#include "CardWidgetController.h"
#include "Components/WidgetComponent.h"
#include "CardGameWidgetComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CARDGAMEPROTO_API UCardGameWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCardGameWidgetComponent();

	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UCardWidgetController* inWidgetController);
	
	UPROPERTY(BlueprintReadOnly, Category="Card UI")
	TObjectPtr<UCardWidgetController> WidgetController;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
