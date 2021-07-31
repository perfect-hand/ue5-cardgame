#pragma once

#include "CoreMinimal.h"

#include "CardGameCardModel.h"
#include "CardGameCardPile.h"
#include "Templates/SubclassOf.h"

#include "CardGameCardPileModel.generated.h"

USTRUCT()
struct CARDGAME_API FCardGameCardPileModel
{
	GENERATED_BODY()

public:
	TSubclassOf<UCardGameCardPile> GetCardPileClass() const;
	void SetCardPileClass(TSubclassOf<UCardGameCardPile> InCardPileClass);
	
private:
	TSubclassOf<UCardGameCardPile> CardPileClass;
	TArray<FCardGameCardModel> Cards;
};
