#pragma once

#include "CoreMinimal.h"

class CARDGAME_API FCardGameCardInstanceIdProvider
{
public:
	FCardGameCardInstanceIdProvider();
	int64 NewId();
	
private:
	int64 NextInstanceId;
};
