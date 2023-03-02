#include "CardGameActor.h"

void ACardGameActor::Init(const FCardGameCardModel& Model, UCardGameCardPile* CardPileClass, int32 PositionInCardPile,
	TOptional<uint8> PlayerIndex)
{
	InstanceId = Model.InstanceId;
	
	NotifyOnInit(Model, CardPileClass, PositionInCardPile, PlayerIndex);
}

int64 ACardGameActor::GetInstanceId() const
{
	return InstanceId;
}

void ACardGameActor::NotifyOnInit(const FCardGameCardModel& Model, UCardGameCardPile* CardPileClass,
                                  int32 PositionInCardPile, TOptional<uint8> PlayerIndex)
{
	ReceiveOnInit(Model, CardPileClass, PositionInCardPile, PlayerIndex.Get(0), PlayerIndex.IsSet());
}
