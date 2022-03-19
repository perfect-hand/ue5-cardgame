#include "Misc/AutomationTest.h"

#include "Assets/CardGameAttribute.h"
#include "Model/CardGameModel.h"
#include "Services/CardGameAttributeService.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGetGlobalAttributeValueTest, "CardGame.AttributeService.GetGlobalAttributeValue", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FGetGlobalAttributeValueTest::RunTest(const FString& Parameters)
{
	// ARRANGE
	FCardGameModel Model;
	UCardGameAttribute* Attribute = NewObject<UCardGameAttribute>();
	
	FCardGameAttributeWithValue AttributeWithValue;
	AttributeWithValue.Attribute = Attribute;
	AttributeWithValue.Value = 2;

	Model.GlobalModel.Attributes.Add(AttributeWithValue);

	// ACT
	constexpr FCardGameAttributeService AttributeService;
	const int32 Result = AttributeService.GetGlobalAttributeValue(Model, Attribute);

	// ASSERT
	TestEqual(TEXT("Attribute Value"), Result, AttributeWithValue.Value);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSetGlobalAttributeValueAddsNewValueTest, "CardGame.AttributeService.SetGlobalAttributeValueAddsNewValue", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FSetGlobalAttributeValueAddsNewValueTest::RunTest(const FString& Parameters)
{
	// ARRANGE
	FCardGameModel Model;
	UCardGameAttribute* Attribute = NewObject<UCardGameAttribute>();
	constexpr int32 NewAttributeValue = 2;
	
	// ACT
	constexpr FCardGameAttributeService AttributeService;
	AttributeService.SetGlobalAttributeValue(Model, Attribute, NewAttributeValue);

	// ASSERT
	TestEqual(TEXT("Number Of Attribute Values"), Model.GlobalModel.Attributes.Num(), 1);
	TestEqual(TEXT("Attribute Reference"), Model.GlobalModel.Attributes[0].Attribute, Attribute);
	TestEqual(TEXT("Attribute Value"), Model.GlobalModel.Attributes[0].Value, NewAttributeValue);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSetGlobalAttributeValueChangesExistingValueTest, "CardGame.AttributeService.SetGlobalAttributeValueChangesExistingValue", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FSetGlobalAttributeValueChangesExistingValueTest::RunTest(const FString& Parameters)
{
	// ARRANGE
	FCardGameModel Model;
	UCardGameAttribute* Attribute = NewObject<UCardGameAttribute>();
	
	FCardGameAttributeWithValue AttributeWithValue;
	AttributeWithValue.Attribute = Attribute;
	AttributeWithValue.Value = 2;

	Model.GlobalModel.Attributes.Add(AttributeWithValue);
	
	constexpr int32 NewAttributeValue = 3;
	
	// ACT
	constexpr FCardGameAttributeService AttributeService;
	AttributeService.SetGlobalAttributeValue(Model, Attribute, NewAttributeValue);

	// ASSERT
	TestEqual(TEXT("Attribute Value"), Model.GlobalModel.Attributes[0].Value, NewAttributeValue);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGetPlayerAttributeValueTest, "CardGame.AttributeService.GetPlayerAttributeValue", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FGetPlayerAttributeValueTest::RunTest(const FString& Parameters)
{
	// ARRANGE
	FCardGameModel Model;
	UCardGameAttribute* Attribute = NewObject<UCardGameAttribute>();
	
	FCardGameAttributeWithValue AttributeWithValue;
	AttributeWithValue.Attribute = Attribute;
	AttributeWithValue.Value = 2;

	FCardGamePlayerModel Player;
	Player.PlayerIndex = 3;
	Player.PlayerModel.Attributes.Add(AttributeWithValue);

	Model.Players.Add(Player);
	
	// ACT
	constexpr FCardGameAttributeService AttributeService;
	const int32 Result = AttributeService.GetPlayerAttributeValue(Model, Player.PlayerIndex, Attribute);

	// ASSERT
	TestEqual(TEXT("Attribute Value"), Result, AttributeWithValue.Value);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSetPlayerAttributeValueAddsNewValueTest, "CardGame.AttributeService.SetPlayerAttributeValueAddsNewValue", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FSetPlayerAttributeValueAddsNewValueTest::RunTest(const FString& Parameters)
{
	// ARRANGE
	FCardGameModel Model;
	UCardGameAttribute* Attribute = NewObject<UCardGameAttribute>();
	constexpr int32 NewAttributeValue = 2;

	FCardGamePlayerModel Player;
	Player.PlayerIndex = 3;
	Model.Players.Add(Player);
	
	// ACT
	constexpr FCardGameAttributeService AttributeService;
	AttributeService.SetPlayerAttributeValue(Model, Player.PlayerIndex, Attribute, NewAttributeValue);

	// ASSERT
	TestEqual(TEXT("Number Of Attribute Values"), Model.Players[0].PlayerModel.Attributes.Num(), 1);
	TestEqual(TEXT("Attribute Reference"), Model.Players[0].PlayerModel.Attributes[0].Attribute, Attribute);
	TestEqual(TEXT("Attribute Value"), Model.Players[0].PlayerModel.Attributes[0].Value, NewAttributeValue);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSetPlayerAttributeValueChangesExistingValueTest, "CardGame.AttributeService.SetPlayerAttributeValueChangesExistingValue", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FSetPlayerAttributeValueChangesExistingValueTest::RunTest(const FString& Parameters)
{
	// ARRANGE
	FCardGameModel Model;
	UCardGameAttribute* Attribute = NewObject<UCardGameAttribute>();
	
	FCardGameAttributeWithValue AttributeWithValue;
	AttributeWithValue.Attribute = Attribute;
	AttributeWithValue.Value = 2;

	FCardGamePlayerModel Player;
	Player.PlayerIndex = 3;
	Player.PlayerModel.Attributes.Add(AttributeWithValue);

	Model.Players.Add(Player);
	
	constexpr int32 NewAttributeValue = 4;
	
	// ACT
	constexpr FCardGameAttributeService AttributeService;
	AttributeService.SetPlayerAttributeValue(Model, Player.PlayerIndex, Attribute, NewAttributeValue);

	// ASSERT
	TestEqual(TEXT("Attribute Value"), Model.Players[0].PlayerModel.Attributes[0].Value, NewAttributeValue);
	return true;
}
