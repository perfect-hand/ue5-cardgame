#pragma once

#include "CoreMinimal.h"

#include "CardGameCardInstanceIdPool.h"
#include "CardGameCardPileModel.h"
#include "CardGameScopedModel.h"

#include "CardGamePlayerModel.generated.h"

class UCardGameCardPile;

USTRUCT()
struct CARDGAME_API FCardGamePlayerModel
{
	GENERATED_BODY()

public:
	uint8 GetPlayerIndex() const;
	void SetPlayerIndex(uint8 InPlayerIndex);
	void AddCardPile(UCardGameCardPile* CardPileClass);
	void AddCardToCardPile(UCardGameCardPile* CardPileClass, UCardGameCard* CardClass);
	void SetCardInstanceIdPool(FCardGameCardInstanceIdPool& InCardInstanceIdPool);
	void ShuffleCardPile(UCardGameCardPile* CardPileClass, FRandomStream& RandomStream);
	
private:
	uint8 PlayerIndex;
	FCardGameScopedModel PlayerModel;
	TArray<FCardGameCardPileModel> PlayerCardPiles;

	FCardGameCardInstanceIdPool CardInstanceIdPool;
};
