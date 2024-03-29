﻿#include "CardGameServiceContext.h"

#include "CardGameActor.h"
#include "CardGamePlayerState.h"
#include "Providers/CardGameRandomNumberProvider.h"
#include "Services/CardGameAttributeService.h"
#include "Services/CardGameCardPileService.h"
#include "Services/CardGameGameplayTagService.h"
#include "Services/CardGamePlayerService.h"

void UCardGameServiceContext::Init(TWeakPtr<FCardGameModel> InModel)
{
	Model = InModel;
	
	RandomNumberProvider = MakeUnique<FCardGameRandomNumberProvider>();

	AttributeService = MakeUnique<FCardGameAttributeService>();
	CardPileService = MakeUnique<FCardGameCardPileService>(*RandomNumberProvider);
	GameplayTagService = MakeUnique<FCardGameGameplayTagService>();
	PlayerService = MakeUnique<FCardGamePlayerService>();
	
	OnCardAddedToGlobalCardPileHandle = CardPileService->OnCardAddedToGlobalCardPile.AddUObject
		(this, &UCardGameServiceContext::NotifyOnCardAddedToGlobalCardPile);
	OnCardAddedToPlayerCardPileHandle = CardPileService->OnCardAddedToPlayerCardPile.AddUObject
		(this, &UCardGameServiceContext::NotifyOnCardAddedToPlayerCardPile);
}

void UCardGameServiceContext::DeInit()
{
	if (CardPileService.IsValid())
	{
		CardPileService->OnCardAddedToGlobalCardPile.Remove(OnCardAddedToGlobalCardPileHandle);
		CardPileService->OnCardAddedToPlayerCardPile.Remove(OnCardAddedToPlayerCardPileHandle);
	}
}

TWeakPtr<const FCardGameModel> UCardGameServiceContext::GetModel() const
{
	return Model;
}

int32 UCardGameServiceContext::GetGlobalAttributeValue(UCardGameAttribute* Attribute) const
{
	return AttributeService->GetGlobalAttributeValue(*Model.Pin(), Attribute);
}

void UCardGameServiceContext::SetGlobalAttributeValue(UCardGameAttribute* Attribute, int32 NewValue)
{
	AttributeService->SetGlobalAttributeValue(*Model.Pin(), Attribute, NewValue);
}

int32 UCardGameServiceContext::GetPlayerAttributeValue(AController* Player, UCardGameAttribute* Attribute) const
{
	if (!IsValid(Player))
	{
		return 0;
	}

	const ACardGamePlayerState* PlayerState = Player->GetPlayerState<ACardGamePlayerState>();

	if (!IsValid(PlayerState))
	{
		return 0;
	}
	
	return AttributeService->GetPlayerAttributeValue(*Model.Pin(), PlayerState->GetPlayerIndex(), Attribute);
}

void UCardGameServiceContext::SetPlayerAttributeValue(AController* Player, UCardGameAttribute* Attribute,
	int32 NewValue)
{
	if (!IsValid(Player))
	{
		return;
	}

	const ACardGamePlayerState* PlayerState = Player->GetPlayerState<ACardGamePlayerState>();

	if (!IsValid(PlayerState))
	{
		return;
	}
	
	return AttributeService->SetPlayerAttributeValue(*Model.Pin(), PlayerState->GetPlayerIndex(), Attribute, NewValue);
}

TOptional<FCardGameCardModel> UCardGameServiceContext::GetCardModel(const ACardGameActor* Card) const
{
	if (!IsValid(Card))
	{
		return TOptional<FCardGameCardModel>();
	}

	return CardPileService->GetCardModelByInstanceId(*Model.Pin(), Card->GetInstanceId());
}

void UCardGameServiceContext::AddGlobalCardPiles(UCardGameConfiguration* Configuration)
{
	CardPileService->AddGlobalCardPiles(*Model.Pin(), Configuration);
}

void UCardGameServiceContext::AddCardToGlobalCardPile(UCardGameCardPile* CardPileClass, UCardGameCard* CardClass)
{
	CardPileService->AddCardToGlobalCardPile(*Model.Pin(), CardPileClass, CardClass);
}

void UCardGameServiceContext::AddCardToPlayerCardPile(AController* Player, UCardGameCardPile* CardPileClass,
	UCardGameCard* CardClass)
{
	if (!IsValid(Player))
	{
		return;
	}

	const ACardGamePlayerState* PlayerState = Player->GetPlayerState<ACardGamePlayerState>();

	if (!IsValid(PlayerState))
	{
		return;
	}

	CardPileService->AddCardToPlayerCardPile(*Model.Pin(), PlayerState->GetPlayerIndex(), CardPileClass, CardClass);
}

void UCardGameServiceContext::ShuffleGlobalCardPile(UCardGameCardPile* CardPileClass)
{
	CardPileService->ShuffleGlobalCardPile(*Model.Pin(), CardPileClass);
}

void UCardGameServiceContext::ShufflePlayerCardPile(AController* Player, UCardGameCardPile* CardPileClass)
{
	if (!IsValid(Player))
	{
		return;
	}

	const ACardGamePlayerState* PlayerState = Player->GetPlayerState<ACardGamePlayerState>();

	if (!IsValid(PlayerState))
	{
		return;
	}

	CardPileService->ShufflePlayerCardPile(*Model.Pin(), PlayerState->GetPlayerIndex(), CardPileClass);
}

void UCardGameServiceContext::MoveCardBetweenGlobalCardPiles(UCardGameCardPile* From, UCardGameCardPile* To,
	int64 CardInstanceId)
{
	CardPileService->MoveCardBetweenGlobalCardPiles(*Model.Pin(), From, To, CardInstanceId);
}

void UCardGameServiceContext::MoveCardBetweenPlayerCardPiles(AController* Player, UCardGameCardPile* From,
                                                             UCardGameCardPile* To, int64 CardInstanceId)
{
	if (!IsValid(Player))
	{
		return;
	}

	const ACardGamePlayerState* PlayerState = Player->GetPlayerState<ACardGamePlayerState>();

	if (!IsValid(PlayerState))
	{
		return;
	}

	CardPileService->MoveCardBetweenPlayerCardPiles(*Model.Pin(), PlayerState->GetPlayerIndex(), From, To, CardInstanceId);
}

void UCardGameServiceContext::MoveLastCardBetweenPlayerCardPiles(AController* Player, UCardGameCardPile* From,
	UCardGameCardPile* To)
{
	if (!IsValid(Player))
	{
		return;
	}

	const ACardGamePlayerState* PlayerState = Player->GetPlayerState<ACardGamePlayerState>();

	if (!IsValid(PlayerState))
	{
		return;
	}

	CardPileService->MoveLastCardBetweenPlayerCardPiles(*Model.Pin(), PlayerState->GetPlayerIndex(), From, To);
}

FGameplayTagContainer UCardGameServiceContext::GetCardGameplayTags(const ACardGameActor* Card) const
{
	if (!IsValid(Card))
	{
		return FGameplayTagContainer();
	}

	TOptional<FCardGameCardModel> CardModel = GetCardModel(Card);

	if (!CardModel.IsSet())
	{
		return FGameplayTagContainer();
	}
	
	return GameplayTagService->GetCardGameplayTags(*Model.Pin(), CardModel.GetValue());
}

void UCardGameServiceContext::AddGlobalGameplayTag(const FGameplayTag& TagToAdd)
{
	GameplayTagService->AddGlobalGameplayTag(*Model.Pin(), TagToAdd);
}

void UCardGameServiceContext::RemoveGlobalGameplayTag(const FGameplayTag& TagToRemove)
{
	GameplayTagService->RemoveGlobalGameplayTag(*Model.Pin(), TagToRemove);
}

int32 UCardGameServiceContext::AddPlayer(const UCardGameConfiguration* Configuration)
{
	return PlayerService->AddPlayer(*Model.Pin(), Configuration);
}

void UCardGameServiceContext::NotifyOnCardAddedToGlobalCardPile(UCardGameCardPile* CardPileClass,
                                                                int32 PositionInCardPile, FCardGameCardModel Card)
{
	OnCardAddedToGlobalCardPile.Broadcast(CardPileClass, PositionInCardPile, Card);
}

void UCardGameServiceContext::NotifyOnCardAddedToPlayerCardPile(uint8 PlayerIndex, UCardGameCardPile* CardPileClass,
	int32 PositionInCardPile, FCardGameCardModel Card)
{
	OnCardAddedToPlayerCardPile.Broadcast(PlayerIndex, CardPileClass, PositionInCardPile, Card);
}
