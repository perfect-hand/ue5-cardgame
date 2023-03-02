#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"

#include "CardGameActorManager.h"
#include "Model/CardGameModel.h"

#include "CardGamePlayerController.generated.h"

class UCardGameServiceContext;
class UCardGameAttribute;


UCLASS()
class CARDGAME_API ACardGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACardGamePlayerController(const FObjectInitializer& ObjectInitializer);

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UFUNCTION(Reliable, Client)
	void ClientGameStarted(const FCardGameModel& InModel);

	virtual void NotifyOnGameStarted();
	
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="On Game Started"))
	void ReceiveOnGameStarted();
	
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCardGameActorManager> ActorManagerClass;
	
	TSharedPtr<FCardGameModel> ClientModel;

	UPROPERTY()
	TObjectPtr<UCardGameServiceContext> Context;
	
	UPROPERTY()
	TObjectPtr<UCardGameActorManager> ActorManager;
};
