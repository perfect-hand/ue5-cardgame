#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"
#include "Templates/SubclassOf.h"

#include "CardGameAbilityEffect.h"
#include "CardGameAttributeWithValue.h"

#include "CardGameScopedModel.generated.h"

class UCardGameAttribute;

USTRUCT()
struct CARDGAME_API FCardGameScopedModel
{
	GENERATED_BODY()

public:
	float GetAttributeValue(UCardGameAttribute* Attribute) const;
	void SetAttributeValue(UCardGameAttribute* Attribute, float NewValue);
	
private:
	UPROPERTY()
	TArray<FCardGameAttributeWithValue> Attributes;

	UPROPERTY()
	FGameplayTagContainer GameplayTags;

	UPROPERTY()
	TArray<TSubclassOf<UCardGameAbilityEffect>> ActiveEffects;
};
