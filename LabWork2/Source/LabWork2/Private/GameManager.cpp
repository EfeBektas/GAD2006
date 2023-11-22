// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "MoveCommand.h"
#include "Command.h"
#include "TBPlayerController.h"


// Sets default values
AGameManager::AGameManager()
{
	PrimaryActorTick.bCanEverTick = true;
}



bool AGameManager::UndoLastMove()
{
	// vvvvvvvvvvvvvvvvvvv

	//if (CurrentCommand.IsValid() && CurrentCommand->IsExecuting()) return false;

	if (CommandPool.Num() < 1)
	{
		return false;

	}

	TSharedRef<Command> Cmd  = CommandPool.Pop();
	Cmd->Revert();
	CurrentCommand = Cmd;



	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s"), UndoLastMove));
	return true;

}

void AGameManager::BeginPlay()
{
	Super::BeginPlay();

	if (auto PlayerController = GWorld->GetFirstPlayerController<ATBPlayerController>())
	{
		PlayerController->GameManager = this;
	}

	if (Levels.IsValidIndex(CurrentLevel))
	{
		CreateLevelActors(Levels[CurrentLevel]);
	}
}

void AGameManager::OnActorClicked(AActor* Actor, FKey button)
{
	if (CurrentCommand.IsValid() && CurrentCommand->IsExecuting()) return;


	AGameSlot* Slot = Cast <AGameSlot>(Actor);

	if (!Slot) return;

	if (!ThePlayer)
	{
		UE_LOG(LogTemp, Error, TEXT("No player unit detected!"));
		return;
	}

	if (Slot->Unit ==nullptr)
	{
		TSharedRef<MoveCommand> Cmd =
			MakeShared<MoveCommand>(ThePlayer->Slot->GridPosition, Slot->GridPosition);

		CommandPool.Add(Cmd);
		Cmd->Execute();
		CurrentCommand = Cmd;
	}
}

void AGameManager::CreateLevelActors(FSLevelInfo& Info)
{

	ThePlayer = nullptr;

	for (auto UnitInfo : Info.Units)
	{
		if (AGameSlot* Slot = GameGrid->GetSlot(UnitInfo.StartPosition))
		{
			Slot->SpawnUnitHere(UnitInfo.UnitClass);
			if (Slot->Unit && Slot->Unit->IsControlledByThePlayer())
			{
				ThePlayer = Slot->Unit;
			}
		}
	}


}



// Called when the game starts or when spawned


// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentCommand.IsValid())
	{
		CurrentCommand->Update(DeltaTime);
	}
}

