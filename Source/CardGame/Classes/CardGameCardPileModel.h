#pragma once

#include "CoreMinimal.h"

#include "CardGameCardModel.h"
#include "CardGameCardPile.h"
#include "Templates/SubclassOf.h"

#include "CardGameCardPileModel.generated.h"

USTRUCT()
struct CARDGAME_API FCardGameCardPileModel
{
	GENERATED_BODY()

private:
	TSubclassOf<UCardGameCardPile> CardPileClass;
	TArray<FCardGameCardModel> Cards;
};
