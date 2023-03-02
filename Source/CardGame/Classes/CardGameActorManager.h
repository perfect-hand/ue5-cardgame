#pragma once

#include "CoreMinimal.h"

#include "UObject/Object.h"
#include "Templates/SubclassOf.h"

#include "CardGameActor.h"
#include "Model/CardGameModel.h"

#include "CardGameActorManager.generated.h"

class UCardGameServiceContext;
struct FCardGameCardModel;

UCLASS(BlueprintType, Blueprintable)
class CARDGAME_API UCardGameActorManager : public UObject
{
	GENERATED_BODY()

public:
	void Init(UCardGameServiceContext* InContext);
	void DeInit();
	
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACardGameActor> CardActorClass;

	UPROPERTY()
	TMap<int64, TObjectPtr<ACardGameActor>> CardActors;

	UPROPERTY()
	TObjectPtr<UCardGameServiceContext> Context;
	
	UFUNCTION()
	void OnCardAddedToGlobalCardPile(UCardGameCardPile* CardPileClass, int32 PositionInCardPile, FCardGameCardModel Card);

	UFUNCTION()
	void OnCardAddedToPlayerCardPile(uint8 PlayerIndex, UCardGameCardPile* CardPileClass, int32 PositionInCardPile,
		FCardGameCardModel Card);

	void SpawnCardActor(UCardGameCardPile* CardPileClass, int32 PositionInCardPile, FCardGameCardModel Card,
		TOptional<uint8> PlayerIndex);
};
