#include "CardGameActorManager.h"

#include "CardGameCard.h"
#include "CardGameCardPile.h"
#include "CardGameLogCategory.h"

void UCardGameActorManager::Init(FCardGameModel& Model)
{
	Model.OnCardAddedToGlobalCardPile.AddDynamic(this, &UCardGameActorManager::OnCardAddedToGlobalCardPile);

	// Raise initial events.
	for (const FCardGameCardPileModel& CardPile : Model.GetGlobalCardPiles())
	{
		for (const FCardGameCardModel& Card : CardPile.GetCards())
		{
			OnCardAddedToGlobalCardPile(CardPile.GetCardPileClass(), Card);
		}
	}
}

void UCardGameActorManager::OnCardAddedToGlobalCardPile(UCardGameCardPile* CardPileClass, FCardGameCardModel Card)
{
	ACardGameActor* CardActor = GetWorld()->SpawnActor<ACardGameActor>(CardActorClass);

	if (!IsValid(CardActor))
	{
		UE_LOG(LogCardGame, Warning, TEXT("Failed to spawn actor for card %s (%d)."),
			*Card.GetCardClass()->GetName(), Card.GetInstanceId());
		return;
	}

	CardActors.Add(Card.GetInstanceId(), CardActor);

	UE_LOG(LogCardGame, Log, TEXT("Spawned actor %s for card %s (%d)."), *CardActor->GetName(),
		*Card.GetCardClass()->GetName(), Card.GetInstanceId());

	CardActor->Init(Card);
}
