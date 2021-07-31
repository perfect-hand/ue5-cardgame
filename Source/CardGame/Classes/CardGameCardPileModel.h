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
	void AddCard(FCardGameCardModel Card);
	FCardGameCardModel GetCard(int32 Index) const;
	void RemoveCard(int32 Index);
	void Shuffle(FRandomStream& RandomStream);
	
private:
	UPROPERTY()
	UCardGameCardPile* CardPileClass;
	
	TArray<FCardGameCardModel> Cards;
};
