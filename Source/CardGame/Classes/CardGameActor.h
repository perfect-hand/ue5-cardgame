#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "CardGameCardModel.h"

#include "CardGameActor.generated.h"

UCLASS(BlueprintType, Blueprintable)
class CARDGAME_API ACardGameActor : public AActor
{
	GENERATED_BODY()

public:
	void Init(const FCardGameCardModel& Model);

	virtual void NotifyOnInit(const FCardGameCardModel& Model);
	
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveOnInit(const FCardGameCardModel& Model);
};
