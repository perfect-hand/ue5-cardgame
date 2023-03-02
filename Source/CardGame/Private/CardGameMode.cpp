#include "CardGameMode.h"

#include "CardGameLogCategory.h"
#include "CardGamePlayerController.h"
#include "CardGamePlayerState.h"

ACardGameMode::ACardGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerStateClass = ACardGamePlayerState::StaticClass();

	Model = MakeShared<FCardGameModel>();
	
	Context = ObjectInitializer.CreateDefaultSubobject<UCardGameServiceContext>(this, TEXT("Context"));
	Context->Init(Model);
}

void ACardGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (Context)
	{
		Context->DeInit();
	}
}

void ACardGameMode::StartGame()
{
	// Add global card piles.
	Context->AddGlobalCardPiles(Configuration);

	// Start game.
	for (const ACardGamePlayerState* P : Players)
	{
		ACardGamePlayerController* PC = Cast<ACardGamePlayerController>(P->GetOwner());

		if (!IsValid(PC))
		{
			continue;
		}

		PC->ClientGameStarted(*Model);
	}
}

UCardGameServiceContext* ACardGameMode::GetContext() const
{
	return Context;
}

FString ACardGameMode::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId,
                                     const FString& Options, const FString& Portal)
{
	FString ErrorMessage = Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
	
	if (!ErrorMessage.IsEmpty())
	{
		return ErrorMessage;
	}

	ACardGamePlayerState* NewPlayer = NewPlayerController->GetPlayerState<ACardGamePlayerState>();

	if (!IsValid(NewPlayer))
	{
		return TEXT("Player " + NewPlayerController->GetName() + " is not using a CardGamePlayerState.");
	}

	// Store player reference.
	Players.Add(NewPlayer);
	
	// Add player to model.
	const int32 NewPlayerIndex = Context->AddPlayer(Configuration);
	
	// Set player index for future model reference.
	NewPlayer->SetPlayerIndex(NewPlayerIndex);

	UE_LOG(LogCardGame, Log, TEXT("Set player index of player %s to %d."), *NewPlayer->GetName(), NewPlayerIndex);

	return ErrorMessage;
}
