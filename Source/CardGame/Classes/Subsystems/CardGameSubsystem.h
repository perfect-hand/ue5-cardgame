#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "CardGameSubsystem.generated.h"

struct FCardGameModel;

UCLASS()
class CARDGAME_API UCardGameSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
protected:
	FCardGameModel& GetModel() const;
};
