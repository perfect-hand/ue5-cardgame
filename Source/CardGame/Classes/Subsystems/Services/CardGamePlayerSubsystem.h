#pragma once

#include "CoreMinimal.h"
#include "Subsystems/CardGameSubsystem.h"

#include "Services/CardGamePlayerService.h"

#include "CardGamePlayerSubsystem.generated.h"

class UCardGameConfiguration;

UCLASS()
class CARDGAME_API UCardGamePlayerSubsystem : public UCardGameSubsystem
{
	GENERATED_BODY()
	
public:
	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	// End USubsystem

	int32 AddPlayer(const UCardGameConfiguration* Configuration);
	
private:
	TUniquePtr<FCardGamePlayerService> PlayerService;
};
