#pragma once

#include "CoreMinimal.h"

class CARDGAME_API FCardGameRandomNumberProvider
{
public:
	FCardGameRandomNumberProvider();

	int32 GetInt(int32 MaxExclusive) const;
	
private:
	FRandomStream RandomStream;
};
