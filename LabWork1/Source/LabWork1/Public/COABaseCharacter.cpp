// Fill out your copyright notice in the Description page of Project Settings.


#include "COABaseCharacter.h"

// Sets default values
ACOABaseCharacter::ACOABaseCharacter() :
	MaxHealth(0.0f),
	Health(0.0f),
	HealingRate(150.0f),
	WalkSpeed(200)



{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ACOABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;



	Health = MaxHealth;

}
void ACOABaseCharacter::OnConstruction(const FTransform& Transform)
{

	Update = false;
}



// Called every frame
void ACOABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Health = FMath::Min(MaxHealth, Health + HealingRate * DeltaTime);
	


	
}


void ACOABaseCharacter::SetHealth(float NewHealth)
{
	Health = NewHealth;

}

float ACOABaseCharacter::GetHealth()
{
	return Health;
}



