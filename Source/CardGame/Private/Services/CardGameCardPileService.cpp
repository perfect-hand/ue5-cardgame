#include "Services/CardGameCardPileService.h"

#include "CardGameLogCategory.h"
#include "Assets/CardGameCard.h"
#include "Assets/CardGameCardPile.h"
#include "Assets/CardGameConfiguration.h"
#include "Model/CardGameCardPileModel.h"
#include "Model/CardGameModel.h"
#include "Providers/CardGameRandomNumberProvider.h"

FCardGameCardPileService::FCardGameCardPileService(FCardGameRandomNumberProvider& RandomNumberProvider)
	: RandomNumberProvider(RandomNumberProvider)
{
}

TOptional<FCardGameCardModel> FCardGameCardPileService::GetCardModelByInstanceId(const FCardGameModel& Model,
	int64 InstanceId) const
{
	return Model.Cards.IsValidIndex(InstanceId) ? Model.Cards[InstanceId] : TOptional<FCardGameCardModel>();
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
	
	const FCardGameCardModel NewCard = AddCard(Model, CardClass);
	CardPile->Cards.Add(NewCard.InstanceId);
	
	UE_LOG(LogCardGame, Log, TEXT("Added %s (%d) to global card pile %s."),
		*CardClass->GetName(), NewCard.InstanceId, *CardPileClass->GetName());

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
		
		const FCardGameCardModel NewCard = AddCard(Model, CardClass);
		CardPile->Cards.Add(NewCard.InstanceId);
	
		UE_LOG(LogCardGame, Log, TEXT("Added %s (%d) to %s of player %d."),
			*CardClass->GetName(), NewCard.InstanceId, *CardPileClass->GetName(), Player.PlayerIndex);

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
	UCardGameCardPile* To, int64 CardInstanceId) const
{
	FCardGameCardPileModel* FromCardPile = GetGlobalCardPile(Model, From);
	FCardGameCardPileModel* ToCardPile = GetGlobalCardPile(Model, To);
	
	if (FromCardPile == nullptr || ToCardPile == nullptr)
	{
		return;
	}

	MoveCardBetweenPiles(*FromCardPile, *ToCardPile, CardInstanceId);

	const FCardGameCardModel Card = Model.Cards[CardInstanceId];
	UE_LOG(LogCardGame, Log, TEXT("Moved %s (%d) from global card pile %s to %s."), *Card.CardClass->GetName(),
		Card.InstanceId, *From->GetName(), *To->GetName());
}

void FCardGameCardPileService::MoveCardBetweenPlayerCardPiles(FCardGameModel& Model, int32 PlayerIndex,
	UCardGameCardPile* From, UCardGameCardPile* To, int64 CardInstanceId) const
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

		MoveCardBetweenPiles(*FromCardPile, *ToCardPile, CardInstanceId);

		const FCardGameCardModel Card = Model.Cards[CardInstanceId];
		UE_LOG(LogCardGame, Log, TEXT("Moved %s (%d) of player %d from %s to %s."), *Card.CardClass->GetName(),
			Card.InstanceId, Player.PlayerIndex, *From->GetName(), *To->GetName());
		return;
	}
}

void FCardGameCardPileService::MoveLastCardBetweenPlayerCardPiles(FCardGameModel& Model, int32 PlayerIndex,
	UCardGameCardPile* From, UCardGameCardPile* To) const
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

		const int64 CardInstanceId = FromCardPile->Cards.Last();
		FromCardPile->Cards.RemoveAt(FromCardPile->Cards.Num() - 1);
		ToCardPile->Cards.Add(CardInstanceId);

		const FCardGameCardModel Card = Model.Cards[CardInstanceId];
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

FCardGameCardModel FCardGameCardPileService::AddCard(FCardGameModel& Model, UCardGameCard* CardClass) const
{
	FCardGameCardModel NewCard;
	NewCard.InstanceId = Model.Cards.Num();
	NewCard.CardClass = CardClass;
	
	for (const auto& InitialAttributeValue : CardClass->GetInitialAttributes())
	{
		FCardGameAttributeWithValue AttributeWithValue(InitialAttributeValue.Key, InitialAttributeValue.Value);
		NewCard.CardModel.Attributes.Add(AttributeWithValue);
	}

	NewCard.CardModel.GameplayTags.AppendTags(CardClass->GetInitialGameplayTags());
	
	Model.Cards.Add(NewCard);
	return NewCard;
}

void FCardGameCardPileService::Shuffle(FCardGameCardPileModel& CardPile) const
{
	TArray<int64> ShuffledCards;

	while (!CardPile.Cards.IsEmpty())
	{
		const int32 RandomIndex = RandomNumberProvider.GetInt(CardPile.Cards.Num());
		ShuffledCards.Add(CardPile.Cards[RandomIndex]);
		CardPile.Cards.RemoveAt(RandomIndex);
	}

	CardPile.Cards = ShuffledCards;
}

void FCardGameCardPileService::MoveCardBetweenPiles(FCardGameCardPileModel& From, FCardGameCardPileModel& To, int64 CardInstanceId) const
{
	// Find in pile.
	for (int32 Index = 0; Index < From.Cards.Num(); ++Index)
	{
		if (From.Cards[Index] != CardInstanceId)
		{
			continue;
		}
		
		From.Cards.RemoveAt(Index);
		To.Cards.Add(CardInstanceId);
		return;
	}
}
