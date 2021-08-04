#include "CardGameModel.h"

#include "CardGameCard.h"
#include "CardGameCardPile.h"
#include "CardGameLogCategory.h"

FCardGameModel::FCardGameModel()
{
	RandomStream = FRandomStream(FName());
}

void FCardGameModel::AddGlobalCardPile(UCardGameCardPile* CardPileClass)
{
	FCardGameCardPileModel NewCardPile;
	NewCardPile.SetCardPileClass(CardPileClass);
	GlobalCardPiles.Add(NewCardPile);
}

void FCardGameModel::AddPlayer(int32 PlayerIndex, TArray<UCardGameCardPile*> CardPileClasses)
{
	FCardGamePlayerModel NewPlayer;
	NewPlayer.SetPlayerIndex(PlayerIndex);

	for (UCardGameCardPile* CardPileClass : CardPileClasses)
	{
		NewPlayer.AddCardPile(CardPileClass);
	}

	Players.Add(NewPlayer);
}

void FCardGameModel::AddCardToGlobalCardPile(UCardGameCardPile* CardPileClass, UCardGameCard* CardClass)
{
	FCardGameCardPileModel* CardPile = GetGlobalCardPile(CardPileClass);

	if (!CardPile)
	{
		return;
	}
	
	int64 NewCardInstanceId = CardInstanceIdPool.NewId();
	CardPile->AddCard(NewCardInstanceId, CardClass);
	
	UE_LOG(LogCardGame, Log, TEXT("Added %s (%d) to global card pile %s."),
		*CardClass->GetName(), NewCardInstanceId, *CardPileClass->GetName());
}

void FCardGameModel::AddCardToPlayerCardPile(int32 PlayerIndex, UCardGameCardPile* CardPileClass, UCardGameCard* CardClass)
{
	for (FCardGamePlayerModel& Player : Players)
	{
		if (Player.GetPlayerIndex() == PlayerIndex)
		{
			Player.AddCardToCardPile(CardPileClass, CardClass, CardInstanceIdPool);
			return;
		}
	}
}

void FCardGameModel::ShuffleGlobalCardPile(UCardGameCardPile* CardPileClass)
{
	FCardGameCardPileModel* CardPile = GetGlobalCardPile(CardPileClass);

	if (!CardPile)
	{
		return;
	}
	
	CardPile->Shuffle(RandomStream);
	
	UE_LOG(LogCardGame, Log, TEXT("Shuffled global card pile %s."), *CardPileClass->GetName());
}

void FCardGameModel::ShufflePlayerCardPile(int32 PlayerIndex, UCardGameCardPile* CardPileClass)
{
	for (FCardGamePlayerModel& Player : Players)
	{
		if (Player.GetPlayerIndex() == PlayerIndex)
		{
			Player.ShuffleCardPile(CardPileClass, RandomStream);
			return;
		}
	}
}

void FCardGameModel::MoveCardBetweenGlobalCardPiles(UCardGameCardPile* From, UCardGameCardPile* To, int32 CardIndex)
{
	FCardGameCardPileModel* FromCardPile = GetGlobalCardPile(From);
	FCardGameCardPileModel* ToCardPile = GetGlobalCardPile(To);
	
	if (!FromCardPile || !ToCardPile)
	{
		return;
	}

	FCardGameCardModel Card = FromCardPile->GetCard(CardIndex);
	ToCardPile->AddCard(Card);
	FromCardPile->RemoveCard(CardIndex);

	UE_LOG(LogCardGame, Log, TEXT("Moved %s (%d) from global card pile %s to %s."), *Card.GetCardClass()->GetName(),
		Card.GetInstanceId(), *From->GetName(), *To->GetName());
}

void FCardGameModel::MoveCardBetweenPlayerCardPiles(int32 PlayerIndex, UCardGameCardPile* From, UCardGameCardPile* To, int32 CardIndex)
{
	for (FCardGamePlayerModel& Player : Players)
	{
		if (Player.GetPlayerIndex() == PlayerIndex)
		{
			Player.MoveCardBetweenPiles(From, To, CardIndex);
			return;
		}
	}
}

float FCardGameModel::GetGlobalAttributeValue(UCardGameAttribute* Attribute) const
{
	return GlobalModel.GetAttributeValue(Attribute);
}

void FCardGameModel::SetGlobalAttributeValue(UCardGameAttribute* Attribute, float NewValue)
{
	GlobalModel.SetAttributeValue(Attribute, NewValue);

	UE_LOG(LogCardGame, Log, TEXT("Set global attribute %s value to %f."), *Attribute->GetName(), NewValue);
}

FCardGameCardPileModel* FCardGameModel::GetGlobalCardPile(UCardGameCardPile* CardPileClass)
{
	for (FCardGameCardPileModel& CardPile : GlobalCardPiles)
	{
		if (CardPile.GetCardPileClass() == CardPileClass)
		{
			return &CardPile;
		}
	}

	return nullptr;
}
