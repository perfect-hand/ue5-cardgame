#pragma once

#include "CoreMinimal.h"

#include "CardGameAttributeSystem.generated.h"

class UCardGameAttribute;
struct FCardGameModel;
struct FCardGameScopedModel;

class CARDGAME_API FCardGameAttributeSystem
{
public:
	float GetAttributeValue(const FCardGameScopedModel& ScopedModel, UCardGameAttribute* Attribute) const;
	void SetAttributeValue(FCardGameScopedModel& ScopedModel, UCardGameAttribute* Attribute, float NewValue) const;
	float GetGlobalAttributeValue(const FCardGameModel& Model, UCardGameAttribute* Attribute) const;
	void SetGlobalAttributeValue(FCardGameModel& Model, UCardGameAttribute* Attribute, float NewValue) const;
};
