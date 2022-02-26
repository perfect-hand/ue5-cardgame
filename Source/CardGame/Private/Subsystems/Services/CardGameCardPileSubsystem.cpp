#include "Subsystems/Services/CardGameCardPileSubsystem.h"

#include "CardGamePlayerState.h"
#include "Services/CardGameCardPileService.h"
#include "Subsystems/Providers/CardGameCardInstanceIdSubsystem.h"
#include "Subsystems/Providers/CardGameRandomNumberSubsystem.h"

void UCardGameCardPileSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const UCardGameCardInstanceIdSubsystem* CardInstanceIdPoolSubsystem =
		Collection.InitializeDependency<UCardGameCardInstanceIdSubsystem>();
	const UCardGameRandomNumberSubsystem* RandomStreamSubsystem =
		Collection.InitializeDependency<UCardGameRandomNumberSubsystem>();

	CardPileService = MakeUnique<FCardGameCardPileService>(
		CardInstanceIdPoolSubsystem->GetCardInstanceIdProvider().Get(),
		RandomStreamSubsystem->GetRandomNumberProvider().Get());
}

void UCardGameCardPileSubsystem::AddCardToGlobalCardPile(UCardGameCardPile* CardPileClass, UCardGameCard* CardClass)
{
	CardPileService->AddCardToGlobalCardPile(GetModel(), CardPileClass, CardClass);
}

void UCardGameCardPileSubsystem::AddCardToPlayerCardPile(AController* Player, UCardGameCardPile* CardPileClass,
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

	CardPileService->AddCardToPlayerCardPile(GetModel(), PlayerState->GetPlayerIndex(), CardPileClass, CardClass);
}

void UCardGameCardPileSubsystem::ShuffleGlobalCardPile(UCardGameCardPile* CardPileClass)
{
	CardPileService->ShuffleGlobalCardPile(GetModel(), CardPileClass);
}

void UCardGameCardPileSubsystem::ShufflePlayerCardPile(AController* Player, UCardGameCardPile* CardPileClass)
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

	CardPileService->ShufflePlayerCardPile(GetModel(), PlayerState->GetPlayerIndex(), CardPileClass);
}

void UCardGameCardPileSubsystem::MoveCardBetweenGlobalCardPiles(UCardGameCardPile* From, UCardGameCardPile* To,
	int32 CardIndex)
{
	CardPileService->MoveCardBetweenGlobalCardPiles(GetModel(), From, To, CardIndex);
}

void UCardGameCardPileSubsystem::MoveCardBetweenPlayerCardPiles(AController* Player, UCardGameCardPile* From,
	UCardGameCardPile* To, int32 CardIndex)
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

	CardPileService->MoveCardBetweenPlayerCardPiles(GetModel(), PlayerState->GetPlayerIndex(), From, To, CardIndex);
}
