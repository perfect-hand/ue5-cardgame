#include "Subsystems/Services/CardGamePlayerSubsystem.h"

#include "Services/CardGamePlayerService.h"

void UCardGamePlayerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	PlayerService = MakeUnique<FCardGamePlayerService>();
}

int32 UCardGamePlayerSubsystem::AddPlayer(const UCardGameConfiguration* Configuration)
{
	return PlayerService->AddPlayer(GetModel(), Configuration);
}
