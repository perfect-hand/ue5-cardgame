#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CardGameScope.h"
#include "CardGameCardPile.generated.h"

UCLASS()
class CARDGAME_API UCardGameCardPile : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	ECardGameScope Scope;
};
