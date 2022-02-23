#pragma once

#include "CoreMinimal.h"

#include "CardGameCardInstanceIdPool.h"
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

	//FCardGameCardInstanceIdPool CardInstanceIdPool;
	//FRandomStream RandomStream = FRandomStream(FName());
};
