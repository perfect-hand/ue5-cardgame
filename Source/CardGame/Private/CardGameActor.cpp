#include "CardGameActor.h"

void ACardGameActor::Init(const FCardGameCardModel& Model, UCardGameCardPile* CardPileClass, TOptional<uint8> PlayerIndex)
{
	NotifyOnInit(Model, CardPileClass, PlayerIndex);
}

void ACardGameActor::NotifyOnInit(const FCardGameCardModel& Model, UCardGameCardPile* CardPileClass, TOptional<uint8> PlayerIndex)
{
	ReceiveOnInit(Model, CardPileClass, PlayerIndex.Get(0), PlayerIndex.IsSet());
}
