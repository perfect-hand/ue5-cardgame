#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

struct FCardGameCardModel;
struct FGameplayTag;
struct FCardGameModel;

class CARDGAME_API FCardGameGameplayTagService
{
public:
	FGameplayTagContainer GetCardGameplayTags(const FCardGameModel& GameModel,
		const FCardGameCardModel& CardModel) const;
	void AddGlobalGameplayTag(FCardGameModel& Model, const FGameplayTag& TagToAdd) const;
	void RemoveGlobalGameplayTag(FCardGameModel& Model, const FGameplayTag& TagToRemove) const;
};
