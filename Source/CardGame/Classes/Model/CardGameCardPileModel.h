#pragma once

#include "CoreMinimal.h"

#include "CardGameCardModel.h"

#include "CardGameCardPileModel.generated.h"

class UCardGameCard;
class UCardGameCardPile;

USTRUCT()
struct CARDGAME_API FCardGameCardPileModel
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UCardGameCardPile* CardPileClass;

	UPROPERTY()
	TArray<FCardGameCardModel> Cards;
};
