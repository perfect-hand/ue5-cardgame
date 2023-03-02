#include "CardGamePlayerController.h"

#include "CardGameLogCategory.h"
#include "CardGameServiceContext.h"

ACardGamePlayerController::ACardGamePlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ActorManagerClass = UCardGameActorManager::StaticClass();
}

void ACardGamePlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (ActorManager)
	{
		ActorManager->DeInit();
	}

	if (Context)
	{
		Context->DeInit();
	}
}

void ACardGamePlayerController::NotifyOnGameStarted()
{
	ReceiveOnGameStarted();
}

void ACardGamePlayerController::ClientGameStarted_Implementation(const FCardGameModel& InModel)
{
	ClientModel = MakeShared<FCardGameModel>();
	*ClientModel = InModel;

	Context = NewObject<UCardGameServiceContext>(this);
	Context->Init(ClientModel);
	
	// Setup actor manager.
	ActorManager = NewObject<UCardGameActorManager>(this, ActorManagerClass);
	ActorManager->Init(Context);

	UE_LOG(LogCardGame, Log, TEXT("Game started!"));
	
	NotifyOnGameStarted();
}
