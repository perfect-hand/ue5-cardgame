#include "CardGamePlayerController.h"

#include "CardGameLogCategory.h"
#include "CardGameModel.h"

float ACardGamePlayerController::GetGlobalAttributeValue(UCardGameAttribute* Attribute) const
{
	return Model.GetGlobalAttributeValue(Attribute);
}

void ACardGamePlayerController::NotifyOnGameStarted()
{
	ReceiveOnGameStarted();
}

void ACardGamePlayerController::ClientGameStarted_Implementation(const FCardGameModel& InModel)
{
	Model = InModel;

	UE_LOG(LogCardGame, Log, TEXT("Game started!"));
	
	NotifyOnGameStarted();
}
