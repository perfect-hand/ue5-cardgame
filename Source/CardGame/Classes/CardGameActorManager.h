#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"

#include "CardGameActor.h"
#include "CardGameModel.h"
#include "Templates/SubclassOf.h"

#include "CardGameActorManager.generated.h"

struct FCardGameCardModel;

UCLASS(BlueprintType, Blueprintable)
class CARDGAME_API UCardGameActorManager : public UObject
{
	GENERATED_BODY()

public:
	void Init(FCardGameModel& Model);

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACardGameActor> CardActorClass;

	UPROPERTY()
	TMap<int64, ACardGameActor*> CardActors;
	
	UFUNCTION()
	void OnCardAddedToGlobalCardPile(UCardGameCardPile* CardPileClass, FCardGameCardModel Card);
};
