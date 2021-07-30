#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CardGamePlayerState.generated.h"


UCLASS()
class CARDGAME_API ACardGamePlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	int32 GetPlayerIndex() const;
	void SetPlayerIndex(int32 InPlayerIndex);
	
private:
	int32 PlayerIndex;
};
