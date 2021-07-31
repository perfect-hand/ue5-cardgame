#pragma once

#include "CoreMinimal.h"

#include "CardGameCardModel.h"

#include "CardGameCardPileModel.generated.h"

class UCardGameCard;
class UCardGameCardPile;

USTRUCT()
struct CARDGAME_API FCardGameCardPileModel
{
	GENERATED_BODY()

public:
	FCardGameCardPileModel();
	
	UCardGameCardPile* GetCardPileClass() const;
	void SetCardPileClass(UCardGameCardPile* InCardPileClass);

	void AddCard(int64 InstanceId, UCardGameCard* CardClass);
	
private:
	UPROPERTY()
	UCardGameCardPile* CardPileClass;
	
	TArray<FCardGameCardModel> Cards;
};
