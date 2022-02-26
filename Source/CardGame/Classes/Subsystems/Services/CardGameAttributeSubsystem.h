#pragma once

#include "CoreMinimal.h"
#include "Subsystems/CardGameSubsystem.h"
#include "CardGameAttributeSubsystem.generated.h"

class UCardGameAttribute;
class FCardGameAttributeService;

UCLASS()
class CARDGAME_API UCardGameAttributeSubsystem : public UCardGameSubsystem
{
	GENERATED_BODY()
	
public:
	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	// End USubsystem

	UFUNCTION(BlueprintPure)
	float GetGlobalAttributeValue(UCardGameAttribute* Attribute) const;

	UFUNCTION(BlueprintCallable)
	void SetGlobalAttributeValue(UCardGameAttribute* Attribute, float NewValue);
	
private:
	TUniquePtr<FCardGameAttributeService> AttributeService;
};
