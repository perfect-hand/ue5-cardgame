#include "Subsystems/Services/CardGameAttributeSubsystem.h"

#include "Services/CardGameAttributeService.h"

void UCardGameAttributeSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	AttributeService = MakeUnique<FCardGameAttributeService>();
}

float UCardGameAttributeSubsystem::GetGlobalAttributeValue(UCardGameAttribute* Attribute) const
{
	return AttributeService->GetGlobalAttributeValue(GetModel(), Attribute);
}

void UCardGameAttributeSubsystem::SetGlobalAttributeValue(UCardGameAttribute* Attribute, float NewValue)
{
	AttributeService->SetGlobalAttributeValue(GetModel(), Attribute, NewValue);
}
