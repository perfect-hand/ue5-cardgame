#include "CardGameActor.h"

void ACardGameActor::Init(const FCardGameCardModel& Model)
{
	NotifyOnInit(Model);
}

void ACardGameActor::NotifyOnInit(const FCardGameCardModel& Model)
{
	ReceiveOnInit(Model);
}
