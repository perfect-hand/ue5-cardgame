#pragma once

#include "CoreMinimal.h"
#include "Assets/CardGameConfiguration.h"
#include "GameFramework/GameModeBase.h"

#include "Model/CardGameModel.h"

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

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UFUNCTION(BlueprintCallable, Category="Card Game")
	void StartGame();

	UFUNCTION(BlueprintPure, Category="Card Game")
	UCardGameServiceContext* GetContext() const;
	
protected:
	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId,
		const FString& Options, const FString& Portal) override;

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCardGameConfiguration> Configuration;
	
	TSharedPtr<FCardGameModel> Model;

	UPROPERTY()
	TObjectPtr<UCardGameServiceContext> Context;
	
	UPROPERTY()
	TArray<TObjectPtr<ACardGamePlayerState>> Players;
};
