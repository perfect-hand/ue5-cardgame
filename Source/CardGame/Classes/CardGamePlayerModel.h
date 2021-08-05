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
	void AddCardToCardPile(UCardGameCardPile* CardPileClass, UCardGameCard* CardClass,
		FCardGameCardInstanceIdPool& CardInstanceIdPool);
	void ShuffleCardPile(UCardGameCardPile* CardPileClass, FRandomStream& RandomStream);
	void MoveCardBetweenPiles(UCardGameCardPile* From, UCardGameCardPile* To, int32 Index);
	
private:
	UPROPERTY()
	uint8 PlayerIndex;

	UPROPERTY()
	FCardGameScopedModel PlayerModel;

	UPROPERTY()
	TArray<FCardGameCardPileModel> PlayerCardPiles;

	FCardGameCardPileModel* GetCardPile(UCardGameCardPile* CardPileClass);
};
