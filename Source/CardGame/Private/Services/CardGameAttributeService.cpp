#include "Services/CardGameAttributeService.h"

#include "CardGameLogCategory.h"
#include "Assets/CardGameAttribute.h"
#include "Model/CardGameAttributeWithValue.h"
#include "Model/CardGameModel.h"
#include "Model/CardGameScopedModel.h"

int32 FCardGameAttributeService::GetGlobalAttributeValue(const FCardGameModel& Model,
	UCardGameAttribute* Attribute) const
{
	return GetAttributeValue(Model.GlobalModel, Attribute);
}

void FCardGameAttributeService::SetGlobalAttributeValue(FCardGameModel& Model, UCardGameAttribute* Attribute,
	int32 NewValue) const
{
	SetAttributeValue(Model.GlobalModel, Attribute, NewValue);

	UE_LOG(LogCardGame, Log, TEXT("Set global attribute %s value to %d."), *Attribute->GetName(), NewValue);
}

int32 FCardGameAttributeService::GetPlayerAttributeValue(const FCardGameModel& Model, int32 PlayerIndex,
	UCardGameAttribute* Attribute) const
{
	for (const FCardGamePlayerModel& Player : Model.Players)
	{
		if (Player.PlayerIndex != PlayerIndex)
		{
			continue;
		}

		return GetAttributeValue(Player.PlayerModel, Attribute);
	}

	return 0;
}

void FCardGameAttributeService::SetPlayerAttributeValue(FCardGameModel& Model, int32 PlayerIndex,
	UCardGameAttribute* Attribute, int32 NewValue) const
{
	for (FCardGamePlayerModel& Player : Model.Players)
	{
		if (Player.PlayerIndex != PlayerIndex)
		{
			continue;
		}

		SetAttributeValue(Player.PlayerModel, Attribute, NewValue);

		UE_LOG(LogCardGame, Log, TEXT("Set player %d attribute %s value to %d."), PlayerIndex, *Attribute->GetName(),
			NewValue);
		return;
	}
}

int32 FCardGameAttributeService::GetAttributeValue(const FCardGameScopedModel& ScopedModel,
                                                   UCardGameAttribute* Attribute) const
{
	for (const FCardGameAttributeWithValue& AttributeWithValue : ScopedModel.Attributes)
	{
		if (AttributeWithValue.Attribute == Attribute)
		{
			return AttributeWithValue.Value;
		}
	}

	return 0.0f;
}

void FCardGameAttributeService::SetAttributeValue(FCardGameScopedModel& ScopedModel, UCardGameAttribute* Attribute,
	int32 NewValue) const
{
	for (FCardGameAttributeWithValue& AttributeWithValue : ScopedModel.Attributes)
	{
		if (AttributeWithValue.Attribute == Attribute)
		{
			AttributeWithValue.Value = NewValue;
			return;
		}
	}

	FCardGameAttributeWithValue NewAttributeWithValue;
	NewAttributeWithValue.Attribute = Attribute;
	NewAttributeWithValue.Value = NewValue;
	ScopedModel.Attributes.Add(NewAttributeWithValue);
}