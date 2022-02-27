#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"
#include "Templates/SubclassOf.h"

#include "Assets/CardGameAbilityEffect.h"
#include "Model/CardGameAttributeWithValue.h"

#include "CardGameScopedModel.generated.h"

class UCardGameAttribute;

USTRUCT()
struct CARDGAME_API FCardGameScopedModel
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<FCardGameAttributeWithValue> Attributes;

	UPROPERTY()
	FGameplayTagContainer GameplayTags;

	UPROPERTY()
	TArray<TSubclassOf<UCardGameAbilityEffect>> ActiveEffects;
};
