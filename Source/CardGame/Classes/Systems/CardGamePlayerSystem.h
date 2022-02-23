#pragma once

#include "CoreMinimal.h"

#include "CardGamePlayerSystem.generated.h"

class UCardGameCard;
class FCardGameCardInstanceIdPool;
class UCardGameCardPile;
struct FCardGameCardPileModel;
class FCardGameCardPileSystem;
struct FCardGameModel;
struct FCardGamePlayerModel;

class CARDGAME_API FCardGamePlayerSystem
{
public:
	void AddPlayer(FCardGameModel& Model, int32 PlayerIndex, TArray<UCardGameCardPile*> CardPileClasses) const;
};
