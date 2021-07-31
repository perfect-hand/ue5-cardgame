#include "CardGameMode.h"

#include "CardGameLogCategory.h"
#include "CardGamePlayerState.h"

ACardGameMode::ACardGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerStateClass = ACardGamePlayerState::StaticClass();
}

void ACardGameMode::AddCardToPlayerCardPile(AController* Player, UCardGameCardPile* CardPileClass,
	UCardGameCard* CardClass)
{
	if (!IsValid(Player))
	{
		return;
	}

	ACardGamePlayerState* PlayerState = Player->GetPlayerState<ACardGamePlayerState>();

	if (!IsValid(PlayerState))
	{
		return;
	}

	Model.AddCardToPlayerCardPile(PlayerState->GetPlayerIndex(), CardPileClass, CardClass);
}

void ACardGameMode::ShufflePlayerCardPile(AController* Player, UCardGameCardPile* CardPileClass)
{
	if (!IsValid(Player))
	{
		return;
	}

	ACardGamePlayerState* PlayerState = Player->GetPlayerState<ACardGamePlayerState>();

	if (!IsValid(PlayerState))
	{
		return;
	}

	Model.ShufflePlayerCardPile(PlayerState->GetPlayerIndex(), CardPileClass);
}

FString ACardGameMode::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId,
                                     const FString& Options, const FString& Portal)
{
	FString ErrorMessage = Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
	
	if (IsValid(NewPlayerController))
	{
		ACardGamePlayerState* NewPlayer = NewPlayerController->GetPlayerState<ACardGamePlayerState>();

		if (IsValid(NewPlayer))
		{
			// Find first available player index.
			int32 NewPlayerIndex = 0;
			bool bPlayerIndexInUse = true;
			
			while (bPlayerIndexInUse)
			{
				bPlayerIndexInUse = IsPlayerIndexInUse(NewPlayerIndex);

				if (bPlayerIndexInUse)
				{
					++NewPlayerIndex;
				}
			}

			// Set player index.
			NewPlayer->SetPlayerIndex(NewPlayerIndex);

			UE_LOG(LogCardGame, Log, TEXT("Set player index of player %s to %d."), *NewPlayer->GetName(), NewPlayerIndex);
			
			// Store player reference.
			Players.Add(NewPlayer);

			// Add player to model.
			Model.AddPlayer(NewPlayerIndex, CardPileClasses);
		}
	}

	return ErrorMessage;
}

bool ACardGameMode::IsPlayerIndexInUse(int32 PlayerIndex) const
{
	for (ACardGamePlayerState* ExistingPlayer : Players)
	{
		if (IsValid(ExistingPlayer) && ExistingPlayer->GetPlayerIndex() == PlayerIndex)
		{
			return true;
		}
	}

	return false;
}
