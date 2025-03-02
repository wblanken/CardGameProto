// Copyright Will Blankenship 2024


#include "AbilitySystem/Data/AttributeInfo.h"

FCardGameAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& attributeTag, bool logNotFound) const
{
	for (const auto& attributeInfo : AttributeInformation)
	{
		if (attributeInfo.AttributeTag.MatchesTagExact(attributeTag))
		{
			return attributeInfo;
		}
	}

	if (logNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find info for tag %s on AttributeInfo %s"), *attributeTag.ToString(), *GetNameSafe(this));
	}

	return FCardGameAttributeInfo();
}
