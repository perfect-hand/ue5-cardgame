#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CardGamePlayerState.generated.h"


UCLASS()
class CARDGAME_API ACardGamePlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void CopyProperties(APlayerState* PlayerState) override;
	
	uint8 GetPlayerIndex() const;
	void SetPlayerIndex(uint8 InPlayerIndex);
	
private:
	UPROPERTY(Replicated)
	uint8 PlayerIndex;
};
