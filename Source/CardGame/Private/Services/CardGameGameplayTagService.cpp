#include "Services/CardGameGameplayTagService.h"

#include "CardGameLogCategory.h"
#include "Model/CardGameModel.h"

FGameplayTagContainer FCardGameGameplayTagService::GetCardGameplayTags(const FCardGameModel& GameModel,
	const FCardGameCardModel& CardModel) const
{
	FGameplayTagContainer Result;
	Result.AppendTags(GameModel.GlobalModel.GameplayTags);
	Result.AppendTags(CardModel.CardModel.GameplayTags);
	return Result;
}

void FCardGameGameplayTagService::AddGlobalGameplayTag(FCardGameModel& Model, const FGameplayTag& TagToAdd) const
{
	Model.GlobalModel.GameplayTags.AddTag(TagToAdd);
	
	UE_LOG(LogCardGame, Log, TEXT("Added global gameplay tag %s."), *TagToAdd.ToString());
}

void FCardGameGameplayTagService::RemoveGlobalGameplayTag(FCardGameModel& Model, const FGameplayTag& TagToRemove) const
{
	Model.GlobalModel.GameplayTags.RemoveTag(TagToRemove);
	
	UE_LOG(LogCardGame, Log, TEXT("Removed global gameplay tag %s."), *TagToRemove.ToString());
}
