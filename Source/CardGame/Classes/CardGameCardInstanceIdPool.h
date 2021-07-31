#pragma once

#include "CoreMinimal.h"

class CARDGAME_API FCardGameCardInstanceIdPool
{
public:
	FCardGameCardInstanceIdPool();
	int64 NewId();
	
private:
	int64 NextInstanceId;
};
