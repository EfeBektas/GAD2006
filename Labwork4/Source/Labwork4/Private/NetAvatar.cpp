// Fill out your copyright notice in the Description page of Project Settings.


#include "NetAvatar.h"
#include "GameFramework/CharacterMovementComponent.h"



ANetAvatar::ANetAvatar():
	Speed(100.0f),
	SpeedMultiplier(10.0f)
{
	//SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	//SpringArm->SetupAttachment(RootComponent);

	//Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	//Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);


}

void ANetAvatar::OnRep_PlayerSpeedChanged()
{
}

void ANetAvatar::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ANetAvatar, Speed);
}

void ANetAvatar::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = Speed;

	// Hocam exeption access violation reading location erroru veriyor blueprintten yaptým
	
	//Camera->bUsePawnControlRotation = false;
	//SpringArm->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ANetAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &ANetAvatar::RunPressed);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &ANetAvatar::RunReleased);

	PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Lookup", this, &ACharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("MoveForward", this, &ANetAvatar::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ANetAvatar::MoveRight);

}

void ANetAvatar::SetSpeedInServer_Implementation(float sped)
{
	Speed = sped;

	if (HasAuthority())
	{
		GetCharacterMovement()->MaxWalkSpeed = Speed;
	}

}


void ANetAvatar::MoveForward(float Amount)
{
	FRotator Rotation = GetController()->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, Amount);
}

void ANetAvatar::MoveRight(float Amount)
{
	FRotator Rotation = GetController()->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(ForwardDirection, Amount);
}

void ANetAvatar::RunPressed()
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("runPRESSEDSDEleased"));
	//GetCharacterMovement()->MaxWalkSpeed = Speed * SpeedMultiplier;
	Speed = Speed * SpeedMultiplier;
	SetSpeedInServer(Speed);
}

void ANetAvatar::RunReleased()
{
	//GetCharacterMovement()->MaxWalkSpeed = Speed;
	Speed = Speed / SpeedMultiplier;
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("runReleased"));
	SetSpeedInServer(Speed);

}

