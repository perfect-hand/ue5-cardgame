#include "CardGameBlueprintFunctionLibrary.h"

#include "CardGameCardModel.h"

int64 UCardGameBlueprintFunctionLibrary::GetCardInstanceId(const FCardGameCardModel& Card)
{
	return Card.GetInstanceId();
}

UCardGameCard* UCardGameBlueprintFunctionLibrary::GetCardClass(const FCardGameCardModel& Card)
{
	return Card.GetCardClass();
}
