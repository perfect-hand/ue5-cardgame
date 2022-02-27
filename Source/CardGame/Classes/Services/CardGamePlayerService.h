#pragma once

#include "CoreMinimal.h"

#include "CardGamePlayerService.generated.h"

class UCardGameConfiguration;
struct FCardGameModel;

class CARDGAME_API FCardGamePlayerService
{
public:
	int32 AddPlayer(FCardGameModel& Model, const UCardGameConfiguration* Configuration) const;

private:
	int32 GetAvailablePlayerIndex(const FCardGameModel& Model) const;
	bool IsPlayerIndexInUse(const FCardGameModel& Model, int32 PlayerIndex) const;
};
