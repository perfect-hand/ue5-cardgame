#pragma once

#include "CoreMinimal.h"

class UCardGameAttribute;
struct FCardGameModel;
struct FCardGameScopedModel;

class CARDGAME_API FCardGameAttributeService
{
public:
	int32 GetGlobalAttributeValue(const FCardGameModel& Model, UCardGameAttribute* Attribute) const;
	void SetGlobalAttributeValue(FCardGameModel& Model, UCardGameAttribute* Attribute, int32 NewValue) const;
	int32 GetPlayerAttributeValue(const FCardGameModel& Model, int32 PlayerIndex, UCardGameAttribute* Attribute) const;
	void SetPlayerAttributeValue(FCardGameModel& Model, int32 PlayerIndex, UCardGameAttribute* Attribute,
		int32 NewValue) const;

private:
	int32 GetAttributeValue(const FCardGameScopedModel& ScopedModel, UCardGameAttribute* Attribute) const;
	void SetAttributeValue(FCardGameScopedModel& ScopedModel, UCardGameAttribute* Attribute, int32 NewValue) const;
};
