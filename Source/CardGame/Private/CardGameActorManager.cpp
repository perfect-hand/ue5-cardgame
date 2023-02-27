#include "CardGameActorManager.h"

#include "Assets/CardGameCard.h"
#include "Assets/CardGameCardPile.h"
#include "CardGameLogCategory.h"
#include "Subsystems/Services/CardGameCardPileSubsystem.h"

void UCardGameActorManager::Init(FCardGameModel& Model)
{
	GetWorld()->GetSubsystem<UCardGameCardPileSubsystem>()->OnCardAddedToGlobalCardPile.AddDynamic
		(this, &UCardGameActorManager::OnCardAddedToGlobalCardPile);
	GetWorld()->GetSubsystem<UCardGameCardPileSubsystem>()->OnCardAddedToPlayerCardPile.AddDynamic
		(this, &UCardGameActorManager::OnCardAddedToPlayerCardPile);
	
	// Raise initial events.
	for (const FCardGameCardPileModel& CardPile : Model.GlobalCardPiles)
	{
		for (const FCardGameCardModel& Card : CardPile.Cards)
		{
			OnCardAddedToGlobalCardPile(CardPile.CardPileClass, Card);
		}
	}

	for (const FCardGamePlayerModel& Player : Model.Players)
	{
		for (const FCardGameCardPileModel& CardPile : Player.PlayerCardPiles)
		{
			for (const FCardGameCardModel& Card : CardPile.Cards)
			{
				OnCardAddedToPlayerCardPile(Player.PlayerIndex, CardPile.CardPileClass, Card);
			}
		}
	}
}

void UCardGameActorManager::OnCardAddedToGlobalCardPile(UCardGameCardPile* CardPileClass, FCardGameCardModel Card)
{
	SpawnCardActor(CardPileClass, Card, TOptional<uint8>());
}

void UCardGameActorManager::OnCardAddedToPlayerCardPile(uint8 PlayerIndex, UCardGameCardPile* CardPileClass,
	FCardGameCardModel Card)
{
	SpawnCardActor(CardPileClass, Card, PlayerIndex);
}

void UCardGameActorManager::SpawnCardActor(UCardGameCardPile* CardPileClass, FCardGameCardModel Card,
	TOptional<uint8> PlayerIndex)
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

	CardActor->Init(Card, CardPileClass, PlayerIndex);
}
