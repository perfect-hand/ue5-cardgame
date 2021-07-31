#pragma once

#include "CoreMinimal.h"

#include "CardGameScopedModel.h"

#include "CardGameCardModel.generated.h"

class UCardGameCard;

USTRUCT()
struct CARDGAME_API FCardGameCardModel
{
	GENERATED_BODY()

public:
	FCardGameCardModel();
	FCardGameCardModel(int64 InInstanceId, UCardGameCard* InCardClass);

	int64 GetInstanceId() const;
	UCardGameCard* GetCardClass() const;
	
private:
	int64 InstanceId;

	UPROPERTY()
	UCardGameCard* CardClass;
	
	FCardGameScopedModel CardModel;
};
