#pragma once

#include "CoreMinimal.h"

#include "CardGameScopedModel.h"

#include "CardGameCardModel.generated.h"

class UCardGameCard;

USTRUCT(BlueprintType)
struct CARDGAME_API FCardGameCardModel
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int64 InstanceId;

	UPROPERTY()
	UCardGameCard* CardClass;

	UPROPERTY()
	FCardGameScopedModel CardModel;
};
