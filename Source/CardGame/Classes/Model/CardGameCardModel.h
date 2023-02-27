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
	FCardGameCardModel()
	{
	}
	
	FCardGameCardModel(int64 InInstanceId, UCardGameCard* InCardClass)
	{
		InstanceId = InInstanceId;
		CardClass = InCardClass;
	}
	
	UPROPERTY()
	int64 InstanceId = 0;

	UPROPERTY(BlueprintReadOnly)
	UCardGameCard* CardClass = nullptr;

	UPROPERTY()
	FCardGameScopedModel CardModel;
};
