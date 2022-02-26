#include "Providers/CardGameRandomNumberProvider.h"

FCardGameRandomNumberProvider::FCardGameRandomNumberProvider()
	: RandomStream(FRandomStream(FName()))
{
}

int32 FCardGameRandomNumberProvider::GetInt(int32 MaxExclusive) const
{
	return RandomStream.RandHelper(MaxExclusive);
}
