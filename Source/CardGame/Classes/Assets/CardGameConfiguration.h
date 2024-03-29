﻿#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CardGameConfiguration.generated.h"

class UCardGameCardPile;

UCLASS()
class CARDGAME_API UCardGameConfiguration : public UDataAsset
{
	GENERATED_BODY()

public:
	TArray<UCardGameCardPile*> GetGlobalCardPileClasses() const;
	TArray<UCardGameCardPile*> GetPlayerCardPileClasses() const;
	void SetGlobalCardPileClasses(TArray<UCardGameCardPile*> InGlobalCardPileClasses);
	void SetPlayerCardPileClasses(TArray<UCardGameCardPile*> InPlayerCardPileClasses);
	
private:
	UPROPERTY(EditDefaultsOnly)
	TArray<UCardGameCardPile*> GlobalCardPileClasses;

	UPROPERTY(EditDefaultsOnly)
	TArray<UCardGameCardPile*> PlayerCardPileClasses;
};
