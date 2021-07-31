#pragma once

#include "CoreMinimal.h"

#include "CardGameCardModel.h"

#include "CardGameCardPileModel.generated.h"

class UCardGameCardPile;

USTRUCT()
struct CARDGAME_API FCardGameCardPileModel
{
	GENERATED_BODY()

public:
	FCardGameCardPileModel();
	
	UCardGameCardPile* GetCardPileClass() const;
	void SetCardPileClass(UCardGameCardPile* InCardPileClass);
	
private:
	UPROPERTY()
	UCardGameCardPile* CardPileClass;
	
	TArray<FCardGameCardModel> Cards;
};
