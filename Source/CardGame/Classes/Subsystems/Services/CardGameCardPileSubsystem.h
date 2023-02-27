#pragma once

#include "CoreMinimal.h"
#include "Subsystems/CardGameSubsystem.h"

#include "Model/CardGameCardModel.h"
#include "Services/CardGameCardPileService.h"

#include "CardGameCardPileSubsystem.generated.h"

class UCardGameCard;
class UCardGameCardPile;
class UCardGameConfiguration;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCardGameCardPileSubsystemCardAddedToGlobalCardPileSignature, UCardGameCardPile*, CardPileClass, int32, PositionInCardPile, FCardGameCardModel, Card);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FCardGameCardPileSubsystemCardAddedToPlayerCardPileSignature, uint8, PlayerIndex, UCardGameCardPile*, CardPileClass, int32, PositionInCardPile, FCardGameCardModel, Card);

UCLASS()
class CARDGAME_API UCardGameCardPileSubsystem : public UCardGameSubsystem
{
	GENERATED_BODY()
	
public:
	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End USubsystem

	void AddGlobalCardPiles(UCardGameConfiguration* Configuration);
	
	UFUNCTION(BlueprintCallable)
	void AddCardToGlobalCardPile(UCardGameCardPile* CardPileClass, UCardGameCard* CardClass);

	UFUNCTION(BlueprintCallable)
	void AddCardToPlayerCardPile(AController* Player, UCardGameCardPile* CardPileClass, UCardGameCard* CardClass);

	UFUNCTION(BlueprintCallable)
	void ShuffleGlobalCardPile(UCardGameCardPile* CardPileClass);

	UFUNCTION(BlueprintCallable)
	void ShufflePlayerCardPile(AController* Player, UCardGameCardPile* CardPileClass);

	UFUNCTION(BlueprintCallable)
	void MoveCardBetweenGlobalCardPiles(UCardGameCardPile* From, UCardGameCardPile* To, int32 CardIndex = 0);
	
	UFUNCTION(BlueprintCallable)
	void MoveCardBetweenPlayerCardPiles(AController* Player, UCardGameCardPile* From, UCardGameCardPile* To, int32 CardIndex = 0);
	
	FCardGameCardPileSubsystemCardAddedToGlobalCardPileSignature OnCardAddedToGlobalCardPile;
	FCardGameCardPileSubsystemCardAddedToPlayerCardPileSignature OnCardAddedToPlayerCardPile;
	
private:
	TUniquePtr<FCardGameCardPileService> CardPileService;

	FDelegateHandle OnCardAddedToGlobalCardPileHandle;
	FDelegateHandle OnCardAddedToPlayerCardPileHandle;
	
	UFUNCTION()
	void NotifyOnCardAddedToGlobalCardPile(UCardGameCardPile* CardPileClass, int32 PositionInCardPile, FCardGameCardModel Card);

	UFUNCTION()
	void NotifyOnCardAddedToPlayerCardPile(uint8 PlayerIndex, UCardGameCardPile* CardPileClass, int32 PositionInCardPile, FCardGameCardModel Card);
};
