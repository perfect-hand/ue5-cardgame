#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "CardGameModel.h"

#include "CardGamePlayerController.generated.h"

class UCardGameAttribute;


UCLASS()
class CARDGAME_API ACardGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	float GetGlobalAttributeValue(UCardGameAttribute* Attribute) const;
	
	UFUNCTION(Reliable, Client)
	void ClientGameStarted(const FCardGameModel& InModel);

	virtual void NotifyOnGameStarted();
	
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveOnGameStarted();
	
private:
	UPROPERTY()
	FCardGameModel Model;
};
