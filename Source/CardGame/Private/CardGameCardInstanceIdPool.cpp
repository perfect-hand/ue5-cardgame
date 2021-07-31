#include "CardGameCardInstanceIdPool.h"

FCardGameCardInstanceIdPool::FCardGameCardInstanceIdPool()
{
	NextInstanceId = 1;
}

int64 FCardGameCardInstanceIdPool::NewId()
{
	return NextInstanceId++;
}
