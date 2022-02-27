#include "Providers/CardGameCardInstanceIdProvider.h"

FCardGameCardInstanceIdProvider::FCardGameCardInstanceIdProvider()
	: NextInstanceId(1)
{
}

int64 FCardGameCardInstanceIdProvider::NewId()
{
	return NextInstanceId++;
}
