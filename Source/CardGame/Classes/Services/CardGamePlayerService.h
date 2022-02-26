#pragma once

#include "CoreMinimal.h"

#include "CardGamePlayerService.generated.h"

class UCardGameCard;
class FCardGameCardInstanceIdProvider;
class UCardGameCardPile;
struct FCardGameCardPileModel;
class FCardGameCardPileSystem;
struct FCardGameModel;
struct FCardGamePlayerModel;

class CARDGAME_API FCardGamePlayerService
{
public:
	void AddPlayer(FCardGameModel& Model, int32 PlayerIndex, TArray<UCardGameCardPile*> CardPileClasses) const;
};
