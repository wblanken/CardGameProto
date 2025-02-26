// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HeroCard.h"

#include "CardDataTable.h"
#include "Card/Widget/CardDescriptionWidget.h"
#include "Card/Widget/CardNameWidget.h"

// Sets default values
AHeroCard::AHeroCard()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AlterEgoNameWidget = CreateDefaultSubobject<UWidgetComponent>("Alter-Ego Name Widget");
	AlterEgoNameWidget->SetupAttachment(CardMesh);
	AlterEgoNameWidget->SetRelativeLocation(FVector(-190.f, 0.f, -2.f));
	AlterEgoNameWidget->SetRelativeRotation(FRotator(270.f, 180.f, 0.f));
	AlterEgoNameWidget->SetPivot(FVector2D(0.5f, 0.5f));
	AlterEgoNameWidget->SetDrawSize(FVector2D(200.f, 50.f));

	AlterEgoDescriptionWidget = CreateDefaultSubobject<UWidgetComponent>("Alter-Ego Description Widget");
	AlterEgoDescriptionWidget->SetupAttachment(CardMesh);
	AlterEgoDescriptionWidget->SetRelativeLocation(FVector(130.f, 0.f, -2.f));
	AlterEgoDescriptionWidget->SetRelativeRotation(FRotator(270.f, 180.f, 0.f));
	AlterEgoDescriptionWidget->SetPivot(FVector2D(0.5f, 0.5f));
	AlterEgoDescriptionWidget->SetDrawSize(FVector2D(300.f, 100.f));

	ThwartWidget = CreateDefaultSubobject<UWidgetComponent>("Thwart Widget");
	ThwartWidget->SetupAttachment(CardMesh);
	ThwartWidget->SetRelativeLocation(FVector(-110.f, 120.f, 2.f));
	ThwartWidget->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	ThwartWidget->SetDrawSize(FVector2D(50.f, 50.f));
	
	AttackWidget = CreateDefaultSubobject<UWidgetComponent>("Attack Widget");
	AttackWidget->SetupAttachment(CardMesh);
	AttackWidget->SetRelativeLocation(FVector(-60.f, 120.f, 2.f));
	AttackWidget->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	AttackWidget->SetDrawSize(FVector2D(50.f, 50.f));
	
	DefenseWidget = CreateDefaultSubobject<UWidgetComponent>("Defense Widget");
	DefenseWidget->SetupAttachment(CardMesh);
	DefenseWidget->SetRelativeLocation(FVector(-10.f, 120.f, 2.f));
	DefenseWidget->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	DefenseWidget->SetDrawSize(FVector2D(50.f, 50.f));

	RecoveryWidget = CreateDefaultSubobject<UWidgetComponent>("Recovery Widget");
	RecoveryWidget->SetupAttachment(CardMesh);
	RecoveryWidget->SetRelativeLocation(FVector(-110.f, -120.f, -2.f));
	RecoveryWidget->SetRelativeRotation(FRotator(270.f, 180.f, 0.f));
	RecoveryWidget->SetDrawSize(FVector2D(50.f, 50.f));
}

void AHeroCard::SetIsAlterEgo(bool isAlterEgo)
{
	IsAlterEgo = isAlterEgo;
	// TODO - Animated flip, and maybe pull up to a generic flip function on the base card class.
	if (IsAlterEgo)
	{
		CardMesh->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	}
	else
	{
		CardMesh->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	}
}

// Called when the game starts or when spawned
void AHeroCard::BeginPlay()
{
	Super::BeginPlay();

	// Make sure we're set to the Alter-Ego side and set up the data for it.
	if (!IsAlterEgo)
	{
		SetIsAlterEgo(true);
	}

	checkf(!AlterEgoData.IsNull(), TEXT("AlterEgoData is null"));

	auto alterEgoData = AlterEgoData.GetRow<FBaseCardData>("");	
	
	auto alterEgoWidget = Cast<UCardNameWidget>(AlterEgoNameWidget->GetWidget());
	alterEgoWidget->SetCardName(*alterEgoData->Name);
	alterEgoWidget->SetIsUnique(alterEgoData->IsUnique);

	auto alterEgoDescriptionWidget = Cast<UCardDescriptionWidget>(AlterEgoDescriptionWidget->GetWidget());	
	alterEgoDescriptionWidget->SetTraits(*alterEgoData->Traits);
	alterEgoDescriptionWidget->SetDescription(*alterEgoData->Text);
	alterEgoDescriptionWidget->SetFlavor(*alterEgoData->FlavorText);
}

