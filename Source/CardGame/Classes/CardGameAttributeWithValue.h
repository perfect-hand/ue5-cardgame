#pragma once

#include "CoreMinimal.h"

#include "CardGameAttributeWithValue.generated.h"

class UCardGameAttribute;

USTRUCT()
struct CARDGAME_API FCardGameAttributeWithValue
{
	GENERATED_BODY()

public:
	UCardGameAttribute* GetAttribute() const;
	float GetValue() const;

	void SetAttribute(UCardGameAttribute* InAttribute);
	void SetValue(float InValue);
	
private:
	UPROPERTY()
	UCardGameAttribute* Attribute = nullptr;

	UPROPERTY()
	float Value = 0.0f;
};
