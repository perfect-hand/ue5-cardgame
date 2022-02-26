#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"

#include "Providers/CardGameCardInstanceIdProvider.h"

#include "CardGameCardInstanceIdSubsystem.generated.h"

UCLASS()
class CARDGAME_API UCardGameCardInstanceIdSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	// End USubsystem

	TSharedRef<FCardGameCardInstanceIdProvider> GetCardInstanceIdProvider() const;
	
private:
	TSharedPtr<FCardGameCardInstanceIdProvider> CardInstanceIdProvider;
};
