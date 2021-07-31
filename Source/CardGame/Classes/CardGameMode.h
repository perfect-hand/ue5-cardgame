#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "CardGameCardPile.h"
#include "CardGameModel.h"

#include "CardGameMode.generated.h"

class ACardGamePlayerState;

UCLASS()
class CARDGAME_API ACardGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACardGameMode(const FObjectInitializer& ObjectInitializer);
	
protected:
	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId,
		const FString& Options, const FString& Portal) override;

private:
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UCardGameCardPile>> CardPileClasses;
	
	UPROPERTY()
	FCardGameModel Model;
	
	UPROPERTY()
	TArray<ACardGamePlayerState*> Players;

	bool IsPlayerIndexInUse(int32 PlayerIndex) const;
};
