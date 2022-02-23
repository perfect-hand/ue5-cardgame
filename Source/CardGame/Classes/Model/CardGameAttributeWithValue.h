#pragma once

#include "CoreMinimal.h"

#include "CardGameAttributeWithValue.generated.h"

class UCardGameAttribute;

USTRUCT()
struct CARDGAME_API FCardGameAttributeWithValue
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UCardGameAttribute* Attribute = nullptr;

	UPROPERTY()
	float Value = 0.0f;
};
