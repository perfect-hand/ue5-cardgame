#include "Subsystems/Providers/CardGameRandomNumberSubsystem.h"

void UCardGameRandomNumberSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	RandomNumberProvider = MakeShared<FCardGameRandomNumberProvider>();
}

TSharedRef<FCardGameRandomNumberProvider> UCardGameRandomNumberSubsystem::GetRandomNumberProvider() const
{
	return RandomNumberProvider.ToSharedRef();
}
