#include "Subsystems/Providers/CardGameCardInstanceIdSubsystem.h"

void UCardGameCardInstanceIdSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	CardInstanceIdProvider = MakeShared<FCardGameCardInstanceIdProvider>();
}

TSharedRef<FCardGameCardInstanceIdProvider> UCardGameCardInstanceIdSubsystem::GetCardInstanceIdProvider() const
{
	return CardInstanceIdProvider.ToSharedRef();
}
