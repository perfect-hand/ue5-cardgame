#include "CardGamePlayerState.h"

#include "Net/UnrealNetwork.h"

void ACardGamePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACardGamePlayerState, PlayerIndex);
	DOREPLIFETIME(ACardGamePlayerState, bReady);
}

void ACardGamePlayerState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	ACardGamePlayerState* CardGamePlayerState = Cast<ACardGamePlayerState>(PlayerState);

	if (!IsValid(CardGamePlayerState))
	{
		return;
	}

	CardGamePlayerState->SetPlayerIndex(PlayerIndex);
	
	if (bReady)
	{
		CardGamePlayerState->SetReady();
	}
}

uint8 ACardGamePlayerState::GetPlayerIndex() const
{
	return PlayerIndex;
}

void ACardGamePlayerState::SetPlayerIndex(uint8 InPlayerIndex)
{
	PlayerIndex = InPlayerIndex;
}

bool ACardGamePlayerState::IsReady() const
{
	return bReady;
}

void ACardGamePlayerState::SetReady()
{
	bReady = true;
}
