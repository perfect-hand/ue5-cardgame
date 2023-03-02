#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "GameplayTagContainer.h"

#include "CardGameAbility.h"

#include "CardGameCard.generated.h"

class UTexture2D;
class UCardGameAttribute;

UCLASS(BlueprintType)
class CARDGAME_API UCardGameCard : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	FText GetCardName() const;
	
	const TMap<UCardGameAttribute*, int32>& GetInitialAttributes() const;
	const FGameplayTagContainer& GetInitialGameplayTags() const;
	
private:
	UPROPERTY(EditDefaultsOnly)
	FText CardName;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CardImage;

	UPROPERTY(EditDefaultsOnly)
	FText GameText;

	UPROPERTY(EditDefaultsOnly)
	FText LoreText;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag CardSet;

	UPROPERTY(EditDefaultsOnly)
	int32 CardSetIndex;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<UCardGameAttribute*, int32> InitialAttributes;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer InitialGameplayTags;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UCardGameAbility>> Abilities;
};
