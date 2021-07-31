#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "CardGameModel.h"

#include "CardGameMode.generated.h"

class AController;

class UCardGameCard;
class UCardGameCardPile;
class ACardGamePlayerState;

UCLASS()
class CARDGAME_API ACardGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACardGameMode(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void AddCardToPlayerCardPile(AController* Player, UCardGameCardPile* CardPileClass, UCardGameCard* CardClass);
	
protected:
	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId,
		const FString& Options, const FString& Portal) override;

private:
	UPROPERTY(EditDefaultsOnly)
	TArray<UCardGameCardPile*> CardPileClasses;
	
	UPROPERTY()
	FCardGameModel Model;
	
	UPROPERTY()
	TArray<ACardGamePlayerState*> Players;

	bool IsPlayerIndexInUse(int32 PlayerIndex) const;
};
