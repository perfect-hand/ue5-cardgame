#pragma once

#include "CoreMinimal.h"

#include "GameplayTagContainer.h"
#include "Templates/SubclassOf.h"

#include "CardGameAbilityEffect.h"
#include "CardGameAttribute.h"

#include "CardGameScopedModel.generated.h"

USTRUCT()
struct CARDGAME_API FCardGameScopedModel
{
	GENERATED_BODY()

private:
	TMap<TSubclassOf<UCardGameAttribute>, float> Attributes;
	FGameplayTagContainer GameplayTags;
	TArray<TSubclassOf<UCardGameAbilityEffect>> ActiveEffects;
};
