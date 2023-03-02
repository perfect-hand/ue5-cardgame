#pragma once

#include "CoreMinimal.h"
#include "Model/CardGameCardModel.h"
#include "Model/CardGameModel.h"
#include "UObject/Object.h"
#include "CardGameServiceContext.generated.h"

class FCardGamePlayerService;
class UCardGameConfiguration;
class UCardGameCard;
class FCardGameAttributeService;
class UCardGameAttribute;
struct FCardGameModel;
class FCardGameRandomNumberProvider;
class FCardGameCardInstanceIdProvider;
class FCardGameCardPileService;
class UCardGameCardPile;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCardGameServiceContextCardAddedToGlobalCardPileSignature, UCardGameCardPile*, CardPileClass, int32, PositionInCardPile, FCardGameCardModel, Card);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FCardGameServiceContextCardAddedToPlayerCardPileSignature, uint8, PlayerIndex, UCardGameCardPile*, CardPileClass, int32, PositionInCardPile, FCardGameCardModel, Card);

/** Provides context for using card game services (e.g. by blueprints or AI), and for registering for events. */
UCLASS(BlueprintType)
class CARDGAME_API UCardGameServiceContext : public UObject
{
	GENERATED_BODY()

public:
	void Init(TWeakPtr<FCardGameModel> InModel);
	void DeInit();

	TWeakPtr<const FCardGameModel> GetModel() const;
	
	UFUNCTION(BlueprintPure, Category="Card Game|Attributes")
	int32 GetGlobalAttributeValue(UCardGameAttribute* Attribute) const;

	UFUNCTION(BlueprintCallable, Category="Card Game|Attributes")
	void SetGlobalAttributeValue(UCardGameAttribute* Attribute, int32 NewValue);

	UFUNCTION(BlueprintPure, Category="Card Game|Attributes")
	int32 GetPlayerAttributeValue(AController* Player, UCardGameAttribute* Attribute) const;

	UFUNCTION(BlueprintCallable, Category="Card Game|Attributes")
	void SetPlayerAttributeValue(AController* Player, UCardGameAttribute* Attribute, int32 NewValue);

	void AddGlobalCardPiles(UCardGameConfiguration* Configuration);
	
	UFUNCTION(BlueprintCallable, Category="Card Game|Card Piles")
	void AddCardToGlobalCardPile(UCardGameCardPile* CardPileClass, UCardGameCard* CardClass);

	UFUNCTION(BlueprintCallable, Category="Card Game|Card Piles")
	void AddCardToPlayerCardPile(AController* Player, UCardGameCardPile* CardPileClass, UCardGameCard* CardClass);

	UFUNCTION(BlueprintCallable, Category="Card Game|Card Piles")
	void ShuffleGlobalCardPile(UCardGameCardPile* CardPileClass);

	UFUNCTION(BlueprintCallable, Category="Card Game|Card Piles")
	void ShufflePlayerCardPile(AController* Player, UCardGameCardPile* CardPileClass);

	UFUNCTION(BlueprintCallable, Category="Card Game|Card Piles")
	void MoveCardBetweenGlobalCardPiles(UCardGameCardPile* From, UCardGameCardPile* To, int32 CardIndex = 0);
	
	UFUNCTION(BlueprintCallable, Category="Card Game|Card Piles")
	void MoveCardBetweenPlayerCardPiles(AController* Player, UCardGameCardPile* From, UCardGameCardPile* To, int32 CardIndex = 0);
	
	int32 AddPlayer(const UCardGameConfiguration* Configuration);
	
	FCardGameServiceContextCardAddedToGlobalCardPileSignature OnCardAddedToGlobalCardPile;
	FCardGameServiceContextCardAddedToPlayerCardPileSignature OnCardAddedToPlayerCardPile;
	
private:
	TWeakPtr<FCardGameModel> Model;
	
	TUniquePtr<FCardGameCardInstanceIdProvider> CardInstanceIdProvider;
	TUniquePtr<FCardGameRandomNumberProvider> RandomNumberProvider;

	TUniquePtr<FCardGameAttributeService> AttributeService;
	TUniquePtr<FCardGameCardPileService> CardPileService;
	TUniquePtr<FCardGamePlayerService> PlayerService;
	
	FDelegateHandle OnCardAddedToGlobalCardPileHandle;
	FDelegateHandle OnCardAddedToPlayerCardPileHandle;
	
	UFUNCTION()
	void NotifyOnCardAddedToGlobalCardPile(UCardGameCardPile* CardPileClass, int32 PositionInCardPile, FCardGameCardModel Card);

	UFUNCTION()
	void NotifyOnCardAddedToPlayerCardPile(uint8 PlayerIndex, UCardGameCardPile* CardPileClass, int32 PositionInCardPile, FCardGameCardModel Card);
};
