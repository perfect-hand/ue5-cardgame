#pragma once

#include "CoreMinimal.h"

#include "CardGameCardPileModel.h"
#include "CardGamePlayerModel.h"
#include "CardGameScopedModel.h"

#include "CardGameModel.generated.h"

USTRUCT()
struct CARDGAME_API FCardGameModel
{
	GENERATED_BODY()

private:
	FCardGameScopedModel GlobalModel;
	TArray<FCardGameCardPileModel> GlobalCardPiles;
	
	TArray<FCardGamePlayerModel> Players;
};
