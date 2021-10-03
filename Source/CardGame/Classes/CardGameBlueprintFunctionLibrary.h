#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CardGameBlueprintFunctionLibrary.generated.h"

class UCardGameCard;
struct FCardGameCardModel;

UCLASS()
class CARDGAME_API UCardGameBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static int64 GetCardInstanceId(const FCardGameCardModel& Card);

	UFUNCTION(BlueprintPure)
	static UCardGameCard* GetCardClass(const FCardGameCardModel& Card);
};
