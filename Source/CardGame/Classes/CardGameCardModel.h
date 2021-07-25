#pragma once

#include "CoreMinimal.h"

#include "CardGameScopedModel.h"

#include "CardGameCardModel.generated.h"

USTRUCT()
struct CARDGAME_API FCardGameCardModel
{
	GENERATED_BODY()

private:
	int64 InstanceId;
	FCardGameScopedModel CardModel;
};
