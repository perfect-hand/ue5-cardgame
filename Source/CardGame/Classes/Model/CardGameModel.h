#pragma once

#include "CoreMinimal.h"

#include "CardGameCardPileModel.h"
#include "CardGamePlayerModel.h"
#include "CardGameScopedModel.h"

#include "CardGameModel.generated.h"

class UCardGameCardPile;

USTRUCT()
struct CARDGAME_API FCardGameModel
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FCardGameScopedModel GlobalModel;

	UPROPERTY()
	TArray<FCardGameCardPileModel> GlobalCardPiles;

	UPROPERTY()
	TArray<FCardGamePlayerModel> Players;

	/** Dense array of all cards, no matter if in any global or player card pile, or not in play anymore. */
	UPROPERTY()
	TArray<FCardGameCardModel> Cards;
};
