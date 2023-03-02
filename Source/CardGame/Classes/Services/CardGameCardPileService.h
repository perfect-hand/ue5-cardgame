#pragma once

#include "CoreMinimal.h"
#include "Model/CardGameCardModel.h"

class UCardGameCard;
class FCardGameCardInstanceIdProvider;
class UCardGameCardPile;
struct FCardGameCardPileModel;
class UCardGameConfiguration;
struct FCardGameModel;
struct FCardGamePlayerModel;
class FCardGameRandomNumberProvider;

DECLARE_MULTICAST_DELEGATE_ThreeParams(FCardGameCardPileSystemCardAddedToGlobalCardPileSignature, UCardGameCardPile* /* CardPileClass */, int32 /* PositionInCardPile */, FCardGameCardModel /* Card */);
DECLARE_MULTICAST_DELEGATE_FourParams(FCardGameCardPileSystemCardAddedToPlayerCardPileSignature, uint8 /* PlayerIndex */, UCardGameCardPile* /* CardPileClass */, int32 /* PositionInCardPile */, FCardGameCardModel /* Card */);

class CARDGAME_API FCardGameCardPileService
{
public:
	explicit FCardGameCardPileService(FCardGameCardInstanceIdProvider& CardInstanceIdProvider,
		FCardGameRandomNumberProvider& RandomNumberProvider);

	TOptional<FCardGameCardModel> GetCardModelByInstanceId(const FCardGameModel& Model, int64 InstanceId) const;
	void AddGlobalCardPiles(FCardGameModel& Model, UCardGameConfiguration* Configuration) const;
	void AddCardToGlobalCardPile(FCardGameModel& Model, UCardGameCardPile* CardPileClass,
		UCardGameCard* CardClass) const;
	void AddCardToPlayerCardPile(FCardGameModel& Model, uint8 PlayerIndex, UCardGameCardPile* CardPileClass,
		UCardGameCard* CardClass) const;
	void ShuffleGlobalCardPile(FCardGameModel& Model, UCardGameCardPile* CardPileClass) const;
	void ShufflePlayerCardPile(FCardGameModel& Model, int32 PlayerIndex, UCardGameCardPile* CardPileClass) const;
	void MoveCardBetweenGlobalCardPiles(FCardGameModel& Model, UCardGameCardPile* From, UCardGameCardPile* To,
		int32 CardIndex) const;
	void MoveCardBetweenPlayerCardPiles(FCardGameModel& Model, int32 PlayerIndex, UCardGameCardPile* From,
		UCardGameCardPile* To, int32 CardIndex) const;

	FCardGameCardPileSystemCardAddedToGlobalCardPileSignature OnCardAddedToGlobalCardPile;
	FCardGameCardPileSystemCardAddedToPlayerCardPileSignature OnCardAddedToPlayerCardPile;
	
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
