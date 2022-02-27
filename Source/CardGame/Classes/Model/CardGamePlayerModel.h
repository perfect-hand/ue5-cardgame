#pragma once

#include "CoreMinimal.h"

#include "CardGameCardPileModel.h"
#include "CardGameScopedModel.h"

#include "CardGamePlayerModel.generated.h"

class UCardGameCardPile;

USTRUCT()
struct CARDGAME_API FCardGamePlayerModel
{
	GENERATED_BODY()

public:
	UPROPERTY()
	uint8 PlayerIndex;

	UPROPERTY()
	FCardGameScopedModel PlayerModel;

	UPROPERTY()
	TArray<FCardGameCardPileModel> PlayerCardPiles;
};
