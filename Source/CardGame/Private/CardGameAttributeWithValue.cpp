#include "CardGameAttributeWithValue.h"

UCardGameAttribute* FCardGameAttributeWithValue::GetAttribute() const
{
	return Attribute;
}

float FCardGameAttributeWithValue::GetValue() const
{
	return Value;
}

void FCardGameAttributeWithValue::SetAttribute(UCardGameAttribute* InAttribute)
{
	Attribute = InAttribute;
}

void FCardGameAttributeWithValue::SetValue(float InValue)
{
	Value = InValue;
}
