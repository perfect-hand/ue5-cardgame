#pragma once

#include "CoreMinimal.h"

#include "CardGameCardInstanceIdPool.h"
#include "CardGameCardPileModel.h"
#include "CardGamePlayerModel.h"
#include "CardGameScopedModel.h"

#include "CardGameModel.generated.h"

class UCardGameCardPile;

USTRUCT()
struct CARDGAME_API FCardGameModel
{
	GENERATED_BODY()

public:
	void AddPlayer(int32 PlayerIndex, TArray<UCardGameCardPile*> CardPileClasses);
	void AddCardToPlayerCardPile(int32 PlayerIndex, UCardGameCardPile* CardPileClass, UCardGameCard* CardClass);
	void ShufflePlayerCardPile(int32 PlayerIndex, UCardGameCardPile* CardPileClass);
	
private:
	FCardGameScopedModel GlobalModel;
	TArray<FCardGameCardPileModel> GlobalCardPiles;
	
	TArray<FCardGamePlayerModel> Players;

	FCardGameCardInstanceIdPool CardInstanceIdPool;
	FRandomStream RandomStream;
};
