#include "CardDataTable.h"

#include "Card.h"

FBaseCardData::FBaseCardData(const FDeckCard& Other)
	: Code(Other.Code)
	, Name(Other.Name)
	, Quantity(Other.Quantity)

{}

FBaseCardData::FBaseCardData(const FSetCard& Other)
	: Code(Other.Code)
	, Name(Other.Name)
	, Quantity(Other.Quantity)
	, SetPosition(Other.SetPosition)
{}
