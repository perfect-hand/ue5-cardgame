﻿#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "GameplayTagContainer.h"

#include "CardGameAbility.h"
#include "CardGameAttribute.h"

#include "CardGameCard.generated.h"


class UTexture2D;


UCLASS()
class CARDGAME_API UCardGameCard : public UObject
{
	GENERATED_BODY()

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
	TMap<TSubclassOf<UCardGameAttribute>, float> InitialAttributes;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer InitialGameplayTags;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UCardGameAbility>> Abilities;
};
