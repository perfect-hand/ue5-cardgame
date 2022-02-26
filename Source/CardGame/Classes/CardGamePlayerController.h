#pragma once

#include "CoreMinimal.h"

#include "CardGameActorManager.h"
#include "GameFramework/PlayerController.h"

#include "CardGameModel.h"

#include "CardGamePlayerController.generated.h"

class UCardGameAttribute;


UCLASS()
class CARDGAME_API ACardGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACardGamePlayerController(const FObjectInitializer& ObjectInitializer);
	
	UFUNCTION(BlueprintPure)
	float GetGlobalAttributeValue(UCardGameAttribute* Attribute) const;
	
	UFUNCTION(Reliable, Client)
	void ClientGameStarted(const FCardGameModel& InModel);

	virtual void NotifyOnGameStarted();
	
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveOnGameStarted();
	
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCardGameActorManager> ActorManagerClass;
	
	UPROPERTY()
	FCardGameModel ClientModel;

	UPROPERTY()
	UCardGameActorManager* ActorManager;
};
