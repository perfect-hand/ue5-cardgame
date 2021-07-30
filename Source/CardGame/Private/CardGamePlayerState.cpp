#include "CardGamePlayerState.h"

int32 ACardGamePlayerState::GetPlayerIndex() const
{
	return PlayerIndex;
}

void ACardGamePlayerState::SetPlayerIndex(int32 InPlayerIndex)
{
	PlayerIndex = InPlayerIndex;
}
