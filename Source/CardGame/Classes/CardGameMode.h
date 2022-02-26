#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Model/CardGameModel.h"
#include "Model/CardGameScope.h"

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

	FCardGameModel& GetModel();

	UFUNCTION(BlueprintCallable)
	void SetPlayerReady(AController* Player);

protected:
	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId,
		const FString& Options, const FString& Portal) override;

	virtual void NotifyOnPreStartGame();
	
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveOnPreStartGame();
	
private:
	UPROPERTY(EditDefaultsOnly)
	TArray<UCardGameCardPile*> CardPileClasses;
	
	UPROPERTY(EditDefaultsOnly)
	int32 NumPlayers;
	
	UPROPERTY()
	FCardGameModel Model;
	
	UPROPERTY()
	TArray<ACardGamePlayerState*> Players;

	TArray<UCardGameCardPile*> GetCardPileClassesByScope(ECardGameScope Scope) const;
	bool IsPlayerIndexInUse(int32 PlayerIndex) const;
};
