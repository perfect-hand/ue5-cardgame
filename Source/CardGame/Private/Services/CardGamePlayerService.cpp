#include "Services/CardGamePlayerService.h"

#include "Assets/CardGameCardPile.h"
#include "Assets/CardGameConfiguration.h"
#include "Model/CardGameCardPileModel.h"
#include "Model/CardGameModel.h"
#include "Model/CardGamePlayerModel.h"

int32 FCardGamePlayerService::AddPlayer(FCardGameModel& Model, const UCardGameConfiguration* Configuration) const
{
	FCardGamePlayerModel NewPlayer;
	NewPlayer.PlayerIndex = GetAvailablePlayerIndex(Model);

	for (UCardGameCardPile* CardPileClass : Configuration->GetPlayerCardPileClasses())
	{
		FCardGameCardPileModel NewCardPile;
		NewCardPile.CardPileClass = CardPileClass;
		NewPlayer.PlayerCardPiles.Add(NewCardPile);
	}

	Model.Players.Add(NewPlayer);

	return NewPlayer.PlayerIndex;
}

int32 FCardGamePlayerService::GetAvailablePlayerIndex(const FCardGameModel& Model) const
{
	int32 NewPlayerIndex = 0;
	bool bPlayerIndexInUse = true;
			
	while (bPlayerIndexInUse)
	{
		bPlayerIndexInUse = IsPlayerIndexInUse(Model, NewPlayerIndex);

		if (bPlayerIndexInUse)
		{
			++NewPlayerIndex;
		}
	}

	return NewPlayerIndex;
}

bool FCardGamePlayerService::IsPlayerIndexInUse(const FCardGameModel& Model, int32 PlayerIndex) const
{
	for (const FCardGamePlayerModel& ExistingPlayer : Model.Players)
	{
		if (ExistingPlayer.PlayerIndex == PlayerIndex)
		{
			return true;
		}
	}

	return false;
}
