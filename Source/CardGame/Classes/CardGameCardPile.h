#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CardGameScope.h"
#include "CardGameCardPile.generated.h"

UCLASS()
class CARDGAME_API UCardGameCardPile : public UDataAsset
{
	GENERATED_BODY()

public:
	ECardGameScope GetScope() const;
	
private:
	UPROPERTY(EditDefaultsOnly)
	ECardGameScope Scope;
};
