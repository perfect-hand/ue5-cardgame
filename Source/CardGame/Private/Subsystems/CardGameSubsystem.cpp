#include "Subsystems/CardGameSubsystem.h"

#include "CardGameMode.h"

FCardGameModel& UCardGameSubsystem::GetModel() const
{
	ACardGameMode* GameMode = GetWorld()->GetAuthGameMode<ACardGameMode>();
	return GameMode->GetModel();
}
