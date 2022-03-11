#include "Subsystems/Services/CardGameAttributeSubsystem.h"

#include "CardGamePlayerState.h"
#include "Services/CardGameAttributeService.h"

void UCardGameAttributeSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	AttributeService = MakeUnique<FCardGameAttributeService>();
}

int32 UCardGameAttributeSubsystem::GetGlobalAttributeValue(UCardGameAttribute* Attribute) const
{
	return AttributeService->GetGlobalAttributeValue(GetModel(), Attribute);
}

void UCardGameAttributeSubsystem::SetGlobalAttributeValue(UCardGameAttribute* Attribute, int32 NewValue)
{
	AttributeService->SetGlobalAttributeValue(GetModel(), Attribute, NewValue);
}

int32 UCardGameAttributeSubsystem::GetPlayerAttributeValue(AController* Player, UCardGameAttribute* Attribute) const
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
	
	return AttributeService->GetPlayerAttributeValue(GetModel(), PlayerState->GetPlayerIndex(), Attribute);
}

void UCardGameAttributeSubsystem::SetPlayerAttributeValue(AController* Player, UCardGameAttribute* Attribute,
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
	
	return AttributeService->SetPlayerAttributeValue(GetModel(), PlayerState->GetPlayerIndex(), Attribute, NewValue);
}
