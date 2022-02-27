#pragma once

#include "CoreMinimal.h"
#include "Providers/CardGameRandomNumberProvider.h"
#include "Subsystems/WorldSubsystem.h"
#include "CardGameRandomNumberSubsystem.generated.h"

UCLASS()
class CARDGAME_API UCardGameRandomNumberSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	// End USubsystem

	TSharedRef<FCardGameRandomNumberProvider> GetRandomNumberProvider() const;
	
private:
	TSharedPtr<FCardGameRandomNumberProvider> RandomNumberProvider;
};
