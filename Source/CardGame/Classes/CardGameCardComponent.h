#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "CardGameCard.h"
#include "CardGameScopedModel.h"

#include "CardGameCardComponent.generated.h"


UCLASS()
class CARDGAME_API UCardGameCardComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	TSubclassOf<UCardGameCard> CardClass;
	FCardGameScopedModel Model;
};
