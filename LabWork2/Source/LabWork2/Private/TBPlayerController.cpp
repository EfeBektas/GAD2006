// Fill out your copyright notice in the Description page of Project Settings.


#include "TBPlayerController.h"





ATBPlayerController::ATBPlayerController()
{
}

void ATBPlayerController::BeginPlay()
{
	bEnableClickEvents = true;
	bShowMouseCursor = true;
	ClickEventKeys.AddUnique(EKeys::RightMouseButton);
}

void ATBPlayerController::OnActorClicked(AActor* Actor, FKey Key)
{
	UE_LOG(LogTemp, Warning, TEXT("OnClicked: %s -%s"), *Actor->GetActorLabel(), *Key.ToString());
	if (GameManager) GameManager->OnActorClicked(Actor, Key);

}
