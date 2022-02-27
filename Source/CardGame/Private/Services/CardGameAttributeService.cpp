#include "Services/CardGameAttributeService.h"

#include "CardGameLogCategory.h"
#include "Assets/CardGameAttribute.h"
#include "Model/CardGameAttributeWithValue.h"
#include "Model/CardGameModel.h"
#include "Model/CardGameScopedModel.h"

float FCardGameAttributeService::GetAttributeValue(const FCardGameScopedModel& ScopedModel,
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
	float NewValue) const
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

float FCardGameAttributeService::GetGlobalAttributeValue(const FCardGameModel& Model,
	UCardGameAttribute* Attribute) const
{
	return GetAttributeValue(Model.GlobalModel, Attribute);
}

void FCardGameAttributeService::SetGlobalAttributeValue(FCardGameModel& Model, UCardGameAttribute* Attribute,
	float NewValue) const
{
	SetAttributeValue(Model.GlobalModel, Attribute, NewValue);

	UE_LOG(LogCardGame, Log, TEXT("Set global attribute %s value to %f."), *Attribute->GetName(), NewValue);
}
