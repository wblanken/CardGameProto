// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/CardActorBase.h"

#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"

// Sets default values
ACardActorBase::ACardActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CardMesh = CreateDefaultSubobject<UStaticMeshComponent>("CardMesh");
	CardMesh->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh> CardMeshAsset(TEXT("/Game/Meshes/card_mesh.card_mesh"));
	if (CardMeshAsset.Succeeded())
	{
		CardMesh->SetStaticMesh(CardMeshAsset.Object);
	}
	
	NameWidget = CreateDefaultSubobject<UWidgetComponent>("Name Widget");
	NameWidget->SetupAttachment(CardMesh);	
	NameWidget->SetRelativeLocation(FVector(-190.f, 0.f, 2.f));
	NameWidget->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	NameWidget->SetPivot(FVector2D(0.5f, 0.5f));
	NameWidget->SetDrawSize(FVector2D(200.f, 50.f));
	
	DescriptionWidget = CreateDefaultSubobject<UWidgetComponent>("Description Widget");
	DescriptionWidget->SetupAttachment(CardMesh);
	DescriptionWidget->SetRelativeLocation(FVector(130.f, 0.f, 2.f));
	DescriptionWidget->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	DescriptionWidget->SetPivot(FVector2D(0.5f, 0.5f));
	DescriptionWidget->SetDrawSize(FVector2D(300.f, 100.f));
}

UAbilitySystemComponent* ACardActorBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void ACardActorBase::BeginPlay()
{
	Super::BeginPlay();
	
	checkf(!CardData.IsNull(), TEXT("Card Data is null"));
}

