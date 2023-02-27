#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Model/CardGameCardModel.h"

#include "CardGameActor.generated.h"

class UCardGameCardPile;
UCLASS(BlueprintType, Blueprintable)
class CARDGAME_API ACardGameActor : public AActor
{
	GENERATED_BODY()

public:
	void Init(const FCardGameCardModel& Model, UCardGameCardPile* CardPileClass, TOptional<uint8> PlayerIndex);

	virtual void NotifyOnInit(const FCardGameCardModel& Model, UCardGameCardPile* CardPileClass, TOptional<uint8> PlayerIndex);
	
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="Init"))
	void ReceiveOnInit(const FCardGameCardModel& Model, UCardGameCardPile* CardPileClass, uint8 PlayerIndex, bool bHasPlayer);
};
