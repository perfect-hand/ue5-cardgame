#include "CardGameActorManager.h"

#include "Assets/CardGameCard.h"
#include "Assets/CardGameCardPile.h"
#include "CardGameLogCategory.h"
#include "Subsystems/Services/CardGameCardPileSubsystem.h"

void UCardGameActorManager::Init(FCardGameModel& Model)
{
	GetWorld()->GetSubsystem<UCardGameCardPileSubsystem>()->OnCardAddedToGlobalCardPile.AddDynamic
		(this, &UCardGameActorManager::OnCardAddedToGlobalCardPile);

	// Raise initial events.
	for (const FCardGameCardPileModel& CardPile : Model.GlobalCardPiles)
	{
		for (const FCardGameCardModel& Card : CardPile.Cards)
		{
			OnCardAddedToGlobalCardPile(CardPile.CardPileClass, Card);
		}
	}
}

void UCardGameActorManager::OnCardAddedToGlobalCardPile(UCardGameCardPile* CardPileClass, FCardGameCardModel Card)
{
	ACardGameActor* CardActor = GetWorld()->SpawnActor<ACardGameActor>(CardActorClass);

	if (!IsValid(CardActor))
	{
		UE_LOG(LogCardGame, Warning, TEXT("Failed to spawn actor for card %s (%d)."),
			*Card.CardClass->GetName(), Card.InstanceId);
		return;
	}

	CardActors.Add(Card.InstanceId, CardActor);

	UE_LOG(LogCardGame, Log, TEXT("Spawned actor %s for card %s (%d)."), *CardActor->GetName(),
		*Card.CardClass->GetName(), Card.InstanceId);

	CardActor->Init(Card);
}
