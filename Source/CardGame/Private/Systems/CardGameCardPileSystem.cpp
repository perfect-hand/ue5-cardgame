#include "Systems/CardGameCardPileSystem.h"

#include "CardGameCard.h"
#include "CardGameCardPile.h"
#include "CardGameLogCategory.h"
#include "Model/CardGameCardPileModel.h"
#include "Model/CardGameModel.h"

FCardGameCardPileSystem::FCardGameCardPileSystem(FCardGameCardInstanceIdPool& CardInstanceIdPool,
	FRandomStream& RandomStream)
	: CardInstanceIdPool(CardInstanceIdPool),
	RandomStream(RandomStream)
{
}

void FCardGameCardPileSystem::AddGlobalCardPile(FCardGameModel& Model, UCardGameCardPile* CardPileClass) const
{
	FCardGameCardPileModel NewCardPile;
	NewCardPile.CardPileClass = CardPileClass;
	Model.GlobalCardPiles.Add(NewCardPile);
}

void FCardGameCardPileSystem::AddCardToGlobalCardPile(FCardGameModel& Model, UCardGameCardPile* CardPileClass,
	UCardGameCard* CardClass) const
{
	FCardGameCardPileModel* CardPile = GetGlobalCardPile(Model, CardPileClass);

	if (CardPile == nullptr)
	{
		return;
	}

	const int64 NewCardInstanceId = CardInstanceIdPool.NewId();
	const FCardGameCardModel NewCard = AddCard(*CardPile, NewCardInstanceId, CardClass);
	
	UE_LOG(LogCardGame, Log, TEXT("Added %s (%d) to global card pile %s."),
		*CardClass->GetName(), NewCardInstanceId, *CardPileClass->GetName());

	// Notify listeners.
	OnCardAddedToGlobalCardPile.Broadcast(CardPileClass, NewCard);
}

void FCardGameCardPileSystem::AddCardToPlayerCardPile(FCardGameModel& Model, int32 PlayerIndex,
	UCardGameCardPile* CardPileClass, UCardGameCard* CardClass) const
{
	for (FCardGamePlayerModel& Player : Model.Players)
	{
		if (Player.PlayerIndex != PlayerIndex)
		{
			continue;
		}

		FCardGameCardPileModel* CardPile = GetPlayerCardPile(Player, CardPileClass);

		if (CardPile == nullptr)
		{
			return;
		}

		const int64 NewCardInstanceId = CardInstanceIdPool.NewId();
		AddCard(*CardPile, NewCardInstanceId, CardClass);
	
		UE_LOG(LogCardGame, Log, TEXT("Added %s (%d) to %s of player %d."),
			*CardClass->GetName(), NewCardInstanceId, *CardPileClass->GetName(), Player.PlayerIndex);
		return;
	}
}

void FCardGameCardPileSystem::ShuffleGlobalCardPile(FCardGameModel& Model, UCardGameCardPile* CardPileClass) const
{
	FCardGameCardPileModel* CardPile = GetGlobalCardPile(Model, CardPileClass);

	if (CardPile == nullptr)
	{
		return;
	}
	
	Shuffle(*CardPile);
	
	UE_LOG(LogCardGame, Log, TEXT("Shuffled global card pile %s."), *CardPileClass->GetName());
}

void FCardGameCardPileSystem::ShufflePlayerCardPile(FCardGameModel& Model, int32 PlayerIndex,
	UCardGameCardPile* CardPileClass) const
{
	for (FCardGamePlayerModel& Player : Model.Players)
	{
		if (Player.PlayerIndex != PlayerIndex)
		{
			continue;
		}

		FCardGameCardPileModel* CardPile = GetPlayerCardPile(Player, CardPileClass);

		if (CardPile == nullptr)
		{
			return;
		}
	
		Shuffle(*CardPile);
	
		UE_LOG(LogCardGame, Log, TEXT("Shuffled %s of player %d."), *CardPileClass->GetName(), Player.PlayerIndex);
		return;
	}
}

void FCardGameCardPileSystem::MoveCardBetweenGlobalCardPiles(FCardGameModel& Model, UCardGameCardPile* From,
	UCardGameCardPile* To, int32 CardIndex) const
{
	FCardGameCardPileModel* FromCardPile = GetGlobalCardPile(Model, From);
	FCardGameCardPileModel* ToCardPile = GetGlobalCardPile(Model, To);
	
	if (FromCardPile == nullptr || ToCardPile == nullptr)
	{
		return;
	}

	const FCardGameCardModel Card = MoveCardBetweenPiles(*FromCardPile, *ToCardPile, CardIndex);

	UE_LOG(LogCardGame, Log, TEXT("Moved %s (%d) from global card pile %s to %s."), *Card.CardClass->GetName(),
		Card.InstanceId, *From->GetName(), *To->GetName());
}

void FCardGameCardPileSystem::MoveCardBetweenPlayerCardPiles(FCardGameModel& Model, int32 PlayerIndex,
	UCardGameCardPile* From, UCardGameCardPile* To, int32 CardIndex) const
{
	for (FCardGamePlayerModel& Player : Model.Players)
	{
		if (Player.PlayerIndex != PlayerIndex)
		{
			continue;
		}

		FCardGameCardPileModel* FromCardPile = GetPlayerCardPile(Player, From);
		FCardGameCardPileModel* ToCardPile = GetPlayerCardPile(Player, To);
	
		if (FromCardPile == nullptr || ToCardPile == nullptr)
		{
			return;
		}

		const FCardGameCardModel Card = MoveCardBetweenPiles(*FromCardPile, *ToCardPile, CardIndex);

		UE_LOG(LogCardGame, Log, TEXT("Moved %s (%d) of player %d from %s to %s."), *Card.CardClass->GetName(),
			Card.InstanceId, Player.PlayerIndex, *From->GetName(), *To->GetName());
		return;
	}
}

FCardGameCardPileModel* FCardGameCardPileSystem::GetGlobalCardPile(FCardGameModel& Model,
	UCardGameCardPile* CardPileClass) const
{
	for (FCardGameCardPileModel& CardPile : Model.GlobalCardPiles)
	{
		if (CardPile.CardPileClass == CardPileClass)
		{
			return &CardPile;
		}
	}

	return nullptr;
}

FCardGameCardPileModel* FCardGameCardPileSystem::GetPlayerCardPile(FCardGamePlayerModel& Player,
	UCardGameCardPile* CardPileClass) const
{
	for (FCardGameCardPileModel& CardPile : Player.PlayerCardPiles)
	{
		if (CardPile.CardPileClass == CardPileClass)
		{
			return &CardPile;
		}
	}

	return nullptr;
}

FCardGameCardModel FCardGameCardPileSystem::AddCard(FCardGameCardPileModel& CardPile, int64 InstanceId,
                                                    UCardGameCard* CardClass) const
{
	FCardGameCardModel NewCard;
	NewCard.InstanceId = InstanceId;
	NewCard.CardClass = CardClass;
	
	CardPile.Cards.Add(NewCard);
	return NewCard;
}

void FCardGameCardPileSystem::Shuffle(FCardGameCardPileModel& CardPile) const
{
	TArray<FCardGameCardModel> ShuffledCards;

	while (!CardPile.Cards.IsEmpty())
	{
		const int32 RandomIndex = RandomStream.RandHelper(CardPile.Cards.Num());
		ShuffledCards.Add(CardPile.Cards[RandomIndex]);
		CardPile.Cards.RemoveAt(RandomIndex);
	}

	CardPile.Cards = ShuffledCards;
}

FCardGameCardModel FCardGameCardPileSystem::MoveCardBetweenPiles(FCardGameCardPileModel& From, FCardGameCardPileModel& To,
	int32 CardIndex) const
{
	FCardGameCardModel Card = From.Cards[CardIndex];
	To.Cards.Add(Card);
	From.Cards.RemoveAt(CardIndex);
	return Card;
}
