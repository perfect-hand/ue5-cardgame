#include "CardGamePlayerController.h"

#include "CardGameLogCategory.h"
#include "CardGameModel.h"

ACardGamePlayerController::ACardGamePlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ActorManagerClass = UCardGameActorManager::StaticClass();
}

float ACardGamePlayerController::GetGlobalAttributeValue(UCardGameAttribute* Attribute) const
{
	return ClientModel.GetGlobalAttributeValue(Attribute);
}

void ACardGamePlayerController::NotifyOnGameStarted()
{
	ReceiveOnGameStarted();
}

void ACardGamePlayerController::ClientGameStarted_Implementation(const FCardGameModel& InModel)
{
	ClientModel = InModel;

	// Setup actor manager.
	ActorManager = NewObject<UCardGameActorManager>(this, ActorManagerClass);
	ActorManager->Init(ClientModel);

	UE_LOG(LogCardGame, Log, TEXT("Game started!"));
	
	NotifyOnGameStarted();
}
