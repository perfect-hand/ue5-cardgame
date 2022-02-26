#pragma once

#include "CoreMinimal.h"

#include "Model/CardGameCardModel.h"

#include "CardGameCardPileService.generated.h"

class UCardGameCard;
class FCardGameCardInstanceIdProvider;
class UCardGameCardPile;
struct FCardGameCardPileModel;
struct FCardGameModel;
struct FCardGamePlayerModel;
class FCardGameRandomNumberProvider;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCardGameCardPileSystemCardAddedToGlobalCardPileSignature, UCardGameCardPile*, CardPileClass, FCardGameCardModel, Card);

class CARDGAME_API FCardGameCardPileService
{
public:
	explicit FCardGameCardPileService(FCardGameCardInstanceIdProvider& CardInstanceIdProvider,
		FCardGameRandomNumberProvider& RandomNumberProvider);
	
	void AddGlobalCardPile(FCardGameModel& Model, UCardGameCardPile* CardPileClass) const;
	void AddCardToGlobalCardPile(FCardGameModel& Model, UCardGameCardPile* CardPileClass,
		UCardGameCard* CardClass) const;
	void AddCardToPlayerCardPile(FCardGameModel& Model, int32 PlayerIndex, UCardGameCardPile* CardPileClass,
		UCardGameCard* CardClass) const;
	void ShuffleGlobalCardPile(FCardGameModel& Model, UCardGameCardPile* CardPileClass) const;
	void ShufflePlayerCardPile(FCardGameModel& Model, int32 PlayerIndex, UCardGameCardPile* CardPileClass) const;
	void MoveCardBetweenGlobalCardPiles(FCardGameModel& Model, UCardGameCardPile* From, UCardGameCardPile* To,
		int32 CardIndex) const;
	void MoveCardBetweenPlayerCardPiles(FCardGameModel& Model, int32 PlayerIndex, UCardGameCardPile* From,
		UCardGameCardPile* To, int32 CardIndex) const;

	FCardGameCardPileSystemCardAddedToGlobalCardPileSignature OnCardAddedToGlobalCardPile;

private:
	FCardGameCardInstanceIdProvider& CardInstanceIdProvider;
	FCardGameRandomNumberProvider& RandomNumberProvider;
	
	FCardGameCardPileModel* GetGlobalCardPile(FCardGameModel& Model, UCardGameCardPile* CardPileClass) const;
	FCardGameCardPileModel* GetPlayerCardPile(FCardGamePlayerModel& Player, UCardGameCardPile* CardPileClass) const;
	FCardGameCardModel AddCard(FCardGameCardPileModel& CardPile, int64 InstanceId, UCardGameCard* CardClass) const;
	void Shuffle(FCardGameCardPileModel& CardPile) const;
	FCardGameCardModel MoveCardBetweenPiles(FCardGameCardPileModel& From, FCardGameCardPileModel& To,
		int32 CardIndex) const;
};
