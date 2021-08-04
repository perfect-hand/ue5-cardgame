#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"
#include "Templates/SubclassOf.h"

#include "CardGameAbilityEffect.h"

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
	TMap<UCardGameAttribute*, float> Attributes;
	FGameplayTagContainer GameplayTags;
	TArray<TSubclassOf<UCardGameAbilityEffect>> ActiveEffects;
};
