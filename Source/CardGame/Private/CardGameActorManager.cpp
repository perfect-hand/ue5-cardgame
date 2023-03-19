#include "CardGameActorManager.h"

#include "Assets/CardGameCard.h"
#include "Assets/CardGameCardPile.h"
#include "CardGameLogCategory.h"

void UCardGameActorManager::Init(UCardGameServiceContext* InContext)
{
	Context = InContext;
	
	Context->OnCardAddedToGlobalCardPile.AddDynamic(this, &UCardGameActorManager::OnCardAddedToGlobalCardPile);
	Context->OnCardAddedToPlayerCardPile.AddDynamic(this, &UCardGameActorManager::OnCardAddedToPlayerCardPile);
	
	// Raise initial events.
	const TSharedPtr<const FCardGameModel> Model = Context->GetModel().Pin();
	
	for (const FCardGameCardPileModel& CardPile : Model->GlobalCardPiles)
	{
		for (int32 Index = 0; Index < CardPile.Cards.Num(); ++Index)
		{
			const int64 InstanceId = CardPile.Cards[Index];
			OnCardAddedToGlobalCardPile(CardPile.CardPileClass, Index, Model->Cards[InstanceId]);
		}
	}

	for (const FCardGamePlayerModel& Player : Model->Players)
	{
		for (const FCardGameCardPileModel& CardPile : Player.PlayerCardPiles)
		{
			for (int32 Index = 0; Index < CardPile.Cards.Num(); ++Index)
			{
				const int64 InstanceId = CardPile.Cards[Index];
				OnCardAddedToPlayerCardPile(Player.PlayerIndex, CardPile.CardPileClass, Index, Model->Cards[InstanceId]);
			}
		}
	}
}

void UCardGameActorManager::DeInit()
{
	Context->OnCardAddedToGlobalCardPile.RemoveDynamic(this, &UCardGameActorManager::OnCardAddedToGlobalCardPile);
	Context->OnCardAddedToPlayerCardPile.RemoveDynamic(this, &UCardGameActorManager::OnCardAddedToPlayerCardPile);
}

void UCardGameActorManager::OnCardAddedToGlobalCardPile(UCardGameCardPile* CardPileClass, int32 PositionInCardPile,
                                                        FCardGameCardModel Card)
{
	SpawnCardActor(CardPileClass, PositionInCardPile, Card, TOptional<uint8>());
}

void UCardGameActorManager::OnCardAddedToPlayerCardPile(uint8 PlayerIndex, UCardGameCardPile* CardPileClass,
	int32 PositionInCardPile, FCardGameCardModel Card)
{
	SpawnCardActor(CardPileClass, PositionInCardPile, Card, PlayerIndex);
}

void UCardGameActorManager::SpawnCardActor(UCardGameCardPile* CardPileClass, int32 PositionInCardPile,
	FCardGameCardModel Card, TOptional<uint8> PlayerIndex)
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

	CardActor->Init(Card, CardPileClass, PositionInCardPile, PlayerIndex);
}
