#pragma once

#include "CoreMinimal.h"
#include "Subsystems/CardGameSubsystem.h"

#include "Services/CardGameAttributeService.h"

#include "CardGameAttributeSubsystem.generated.h"

class UCardGameAttribute;

UCLASS()
class CARDGAME_API UCardGameAttributeSubsystem : public UCardGameSubsystem
{
	GENERATED_BODY()
	
public:
	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	// End USubsystem

	UFUNCTION(BlueprintPure)
	int32 GetGlobalAttributeValue(UCardGameAttribute* Attribute) const;

	UFUNCTION(BlueprintCallable)
	void SetGlobalAttributeValue(UCardGameAttribute* Attribute, int32 NewValue);

	UFUNCTION(BlueprintPure)
	int32 GetPlayerAttributeValue(AController* Player, UCardGameAttribute* Attribute) const;

	UFUNCTION(BlueprintCallable)
	void SetPlayerAttributeValue(AController* Player, UCardGameAttribute* Attribute, int32 NewValue);
	
private:
	TUniquePtr<FCardGameAttributeService> AttributeService;
};
