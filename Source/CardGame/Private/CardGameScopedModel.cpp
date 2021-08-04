#include "CardGameScopedModel.h"

float FCardGameScopedModel::GetAttributeValue(UCardGameAttribute* Attribute) const
{
	return Attributes.FindRef(Attribute);
}

void FCardGameScopedModel::SetAttributeValue(UCardGameAttribute* Attribute, float NewValue)
{
	Attributes.Add(Attribute, NewValue);
}
