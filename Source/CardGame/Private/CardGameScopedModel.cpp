#include "CardGameScopedModel.h"

float FCardGameScopedModel::GetAttributeValue(UCardGameAttribute* Attribute) const
{
	for (const FCardGameAttributeWithValue& AttributeWithValue : Attributes)
	{
		if (AttributeWithValue.GetAttribute() == Attribute)
		{
			return AttributeWithValue.GetValue();
		}
	}

	return 0.0f;
}

void FCardGameScopedModel::SetAttributeValue(UCardGameAttribute* Attribute, float NewValue)
{
	for (FCardGameAttributeWithValue& AttributeWithValue : Attributes)
	{
		if (AttributeWithValue.GetAttribute() == Attribute)
		{
			AttributeWithValue.SetValue(NewValue);
			return;
		}
	}

	FCardGameAttributeWithValue NewAttributeWithValue;
	NewAttributeWithValue.SetAttribute(Attribute);
	NewAttributeWithValue.SetValue(NewValue);
	Attributes.Add(NewAttributeWithValue);
}
