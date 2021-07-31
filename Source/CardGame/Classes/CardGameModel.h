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
	void AddPlayer(int32 PlayerIndex, TArray<UCardGameCardPile*> CardPileClasses);
	
private:
	FCardGameScopedModel GlobalModel;
	TArray<FCardGameCardPileModel> GlobalCardPiles;
	
	TArray<FCardGamePlayerModel> Players;
};
