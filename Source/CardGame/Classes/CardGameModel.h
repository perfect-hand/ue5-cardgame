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
	FCardGameModel();

	void AddGlobalCardPile(UCardGameCardPile* CardPileClass);
	void AddPlayer(int32 PlayerIndex, TArray<UCardGameCardPile*> CardPileClasses);
	void AddCardToGlobalCardPile(UCardGameCardPile* CardPileClass, UCardGameCard* CardClass);
	void AddCardToPlayerCardPile(int32 PlayerIndex, UCardGameCardPile* CardPileClass, UCardGameCard* CardClass);
	void ShuffleGlobalCardPile(UCardGameCardPile* CardPileClass);
	void ShufflePlayerCardPile(int32 PlayerIndex, UCardGameCardPile* CardPileClass);
	void MoveCardBetweenGlobalCardPiles(UCardGameCardPile* From, UCardGameCardPile* To, int32 CardIndex);
	void MoveCardBetweenPlayerCardPiles(int32 PlayerIndex, UCardGameCardPile* From, UCardGameCardPile* To, int32 CardIndex);
	
private:
	FCardGameScopedModel GlobalModel;
	TArray<FCardGameCardPileModel> GlobalCardPiles;
	
	TArray<FCardGamePlayerModel> Players;

	FCardGameCardInstanceIdPool CardInstanceIdPool;
	FRandomStream RandomStream;

	FCardGameCardPileModel* GetGlobalCardPile(UCardGameCardPile* CardPileClass);
};
