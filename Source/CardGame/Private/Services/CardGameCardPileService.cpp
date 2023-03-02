#include "Services/CardGameCardPileService.h"

#include "CardGameLogCategory.h"
#include "Assets/CardGameCard.h"
#include "Assets/CardGameCardPile.h"
#include "Assets/CardGameConfiguration.h"
#include "Model/CardGameCardPileModel.h"
#include "Model/CardGameModel.h"
#include "Providers/CardGameCardInstanceIdProvider.h"
#include "Providers/CardGameRandomNumberProvider.h"

FCardGameCardPileService::FCardGameCardPileService(FCardGameCardInstanceIdProvider& CardInstanceIdProvider,
                                                 FCardGameRandomNumberProvider& RandomNumberProvider)
	: CardInstanceIdProvider(CardInstanceIdProvider),
	RandomNumberProvider(RandomNumberProvider)
{
}

TOptional<FCardGameCardModel> FCardGameCardPileService::GetCardModelByInstanceId(const FCardGameModel& Model,
	int64 InstanceId) const
{
	for (const FCardGameCardPileModel& GlobalCardPile : Model.GlobalCardPiles)
	{
		for (const FCardGameCardModel& Card : GlobalCardPile.Cards)
		{
			if (Card.InstanceId == InstanceId)
			{
				return Card;
			}
		}
	}

	for (const FCardGamePlayerModel& Player : Model.Players)
	{
		for (const FCardGameCardPileModel& GlobalCardPile : Player.PlayerCardPiles)
		{
			for (const FCardGameCardModel& Card : GlobalCardPile.Cards)
			{
				if (Card.InstanceId == InstanceId)
				{
					return Card;
				}
			}
		}
	}

	return TOptional<FCardGameCardModel>();
}

void FCardGameCardPileService::AddGlobalCardPiles(FCardGameModel& Model, UCardGameConfiguration* Configuration) const
{
	for (UCardGameCardPile* CardPileClass : Configuration->GetGlobalCardPileClasses())
	{
		FCardGameCardPileModel NewCardPile;
		NewCardPile.CardPileClass = CardPileClass;
		Model.GlobalCardPiles.Add(NewCardPile);
	}
}

void FCardGameCardPileService::AddCardToGlobalCardPile(FCardGameModel& Model, UCardGameCardPile* CardPileClass,
	UCardGameCard* CardClass) const
{
	FCardGameCardPileModel* CardPile = GetGlobalCardPile(Model, CardPileClass);

	if (CardPile == nullptr)
	{
		return;
	}

	const int64 NewCardInstanceId = CardInstanceIdProvider.NewId();
	const FCardGameCardModel NewCard = AddCard(*CardPile, NewCardInstanceId, CardClass);
	
	UE_LOG(LogCardGame, Log, TEXT("Added %s (%d) to global card pile %s."),
		*CardClass->GetName(), NewCardInstanceId, *CardPileClass->GetName());

	// Notify listeners.
	OnCardAddedToGlobalCardPile.Broadcast(CardPileClass, CardPile->Cards.Num(), NewCard);
}

void FCardGameCardPileService::AddCardToPlayerCardPile(FCardGameModel& Model, uint8 PlayerIndex,
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

		const int64 NewCardInstanceId = CardInstanceIdProvider.NewId();
		const FCardGameCardModel NewCard = AddCard(*CardPile, NewCardInstanceId, CardClass);
	
		UE_LOG(LogCardGame, Log, TEXT("Added %s (%d) to %s of player %d."),
			*CardClass->GetName(), NewCardInstanceId, *CardPileClass->GetName(), Player.PlayerIndex);

		// Notify listeners.
		OnCardAddedToPlayerCardPile.Broadcast(PlayerIndex, CardPileClass, CardPile->Cards.Num(), NewCard);
		return;
	}
}

void FCardGameCardPileService::ShuffleGlobalCardPile(FCardGameModel& Model, UCardGameCardPile* CardPileClass) const
{
	FCardGameCardPileModel* CardPile = GetGlobalCardPile(Model, CardPileClass);

	if (CardPile == nullptr)
	{
		return;
	}
	
	Shuffle(*CardPile);
	
	UE_LOG(LogCardGame, Log, TEXT("Shuffled global card pile %s."), *CardPileClass->GetName());
}

void FCardGameCardPileService::ShufflePlayerCardPile(FCardGameModel& Model, int32 PlayerIndex,
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

void FCardGameCardPileService::MoveCardBetweenGlobalCardPiles(FCardGameModel& Model, UCardGameCardPile* From,
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

void FCardGameCardPileService::MoveCardBetweenPlayerCardPiles(FCardGameModel& Model, int32 PlayerIndex,
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

FCardGameCardPileModel* FCardGameCardPileService::GetGlobalCardPile(FCardGameModel& Model,
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

FCardGameCardPileModel* FCardGameCardPileService::GetPlayerCardPile(FCardGamePlayerModel& Player,
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

FCardGameCardModel FCardGameCardPileService::AddCard(FCardGameCardPileModel& CardPile, int64 InstanceId,
                                                    UCardGameCard* CardClass) const
{
	FCardGameCardModel NewCard;
	NewCard.InstanceId = InstanceId;
	NewCard.CardClass = CardClass;
	
	for (const auto& InitialAttributeValue : CardClass->GetInitialAttributes())
	{
		FCardGameAttributeWithValue AttributeWithValue(InitialAttributeValue.Key, InitialAttributeValue.Value);
		NewCard.CardModel.Attributes.Add(AttributeWithValue);
	}

	NewCard.CardModel.GameplayTags.AppendTags(CardClass->GetInitialGameplayTags());
	
	CardPile.Cards.Add(NewCard);
	return NewCard;
}

void FCardGameCardPileService::Shuffle(FCardGameCardPileModel& CardPile) const
{
	TArray<FCardGameCardModel> ShuffledCards;

	while (!CardPile.Cards.IsEmpty())
	{
		const int32 RandomIndex = RandomNumberProvider.GetInt(CardPile.Cards.Num());
		ShuffledCards.Add(CardPile.Cards[RandomIndex]);
		CardPile.Cards.RemoveAt(RandomIndex);
	}

	CardPile.Cards = ShuffledCards;
}

FCardGameCardModel FCardGameCardPileService::MoveCardBetweenPiles(FCardGameCardPileModel& From, FCardGameCardPileModel& To,
	int32 CardIndex) const
{
	FCardGameCardModel Card = From.Cards[CardIndex];
	To.Cards.Add(Card);
	From.Cards.RemoveAt(CardIndex);
	return Card;
}
