#pragma once

#include "CoreMinimal.h"

#include "CardGameCardPileModel.h"
#include "CardGameScopedModel.h"

#include "CardGamePlayerModel.generated.h"

USTRUCT()
struct CARDGAME_API FCardGamePlayerModel
{
	GENERATED_BODY()

private:
	int32 PlayerIndex;
	FCardGameScopedModel PlayerModel;
	TArray<FCardGameCardPileModel> PlayerCardPiles;
};
