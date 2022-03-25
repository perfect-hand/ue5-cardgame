#pragma once

#include "CoreMinimal.h"

#include "CardGameAttributeWithValue.generated.h"

class UCardGameAttribute;

USTRUCT()
struct CARDGAME_API FCardGameAttributeWithValue
{
	GENERATED_BODY()

public:
	FCardGameAttributeWithValue()
	{
	}
	
	FCardGameAttributeWithValue(UCardGameAttribute* InAttribute, int32 InValue)
	{
		Attribute = InAttribute;
		Value = InValue;
	}
	
	UPROPERTY()
	UCardGameAttribute* Attribute = nullptr;

	UPROPERTY()
	int32 Value = 0;
};
