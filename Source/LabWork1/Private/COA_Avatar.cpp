// Fill out your copyright notice in the Description page of Project Settings.


#include "COA_Avatar.h"


ACOA_Avatar::ACOA_Avatar() :

	Stamina(10),
	MaxStamina(10),
	StaminaGainRate(100),
	StaminaDrainRate(100),
	IsRunning(false),
	RunSpeed(450),
	StaminaDrained(false),
	HoldingRunKey()
{

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = 300;
	SpringArm->SetupAttachment(RootComponent);


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	SpringArm->bUsePawnControlRotation = true;
	Camera->bUsePawnControlRotation = false;

}
void ACOA_Avatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Walking) 
	{
		if (!StaminaDrained && HoldingRunKey)
		{
			if (GetCharacterMovement()->Velocity.IsNearlyZero(0.01f))
			{

				Stamina = FMath::Max(0, Stamina - StaminaDrainRate * DeltaTime);
				if (Stamina== 0.0f)
				{
					StaminaDrained = true;
					UpdateMovementParams();
				}
			}
		}
		else
		{
			Stamina = FMath::Min(MaxStamina, Stamina + StaminaGainRate * DeltaTime);
			if (Stamina>= MaxStamina)
			{
				StaminaDrained == false;
				UpdateMovementParams();
			}
		}
	}

	if (IsRunning && StaminaDrained != true)
	{
		Stamina = FMath::Max(0, Stamina - StaminaDrainRate * DeltaTime);
		if (Stamina == 0)
		{
			StaminaDrained = true;
			GEngine->AddOnScreenDebugMessage(0, 0.1f, FColor::Cyan, TEXT("StaminaGone"));
			GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
			IsRunning = false;

		}
	}
	if (GetCharacterMovement()->Velocity == FVector::ZeroVector)
	{
		Stamina = FMath::Min(MaxStamina, Stamina + StaminaGainRate * DeltaTime);

	}
	if (Stamina == MaxStamina)
	{
		StaminaDrained = false;
		GEngine->AddOnScreenDebugMessage(0, 1, FColor::Cyan, TEXT("Ready2Run"));

	}
	GEngine->AddOnScreenDebugMessage(0, 0.1f, FColor::Cyan, FString::Printf(TEXT("%f"), Stamina));
}
void ACOA_Avatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACOA_Avatar::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACOA_Avatar::MoveRight);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ACOA_Avatar::RunPressed);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ACOA_Avatar::RunReleased);
}
void ACOA_Avatar::BeginPlay()
{
	Super::BeginPlay();

	MaxStamina = 200;
	Stamina = MaxStamina;
}

void ACOA_Avatar::OnConstruction(const FTransform& Transform)
{

}
void ACOA_Avatar::MoveForward(float Amount)
{
	FRotator ControlRotation = GetControlRotation();
	FVector ForwardDirection = FRotationMatrix(FRotator(0.0f, ControlRotation.Yaw, 0.0f)).GetUnitAxis(EAxis::X);

	AddMovementInput(ForwardDirection, Amount);
}

void ACOA_Avatar::MoveRight(float Amount)
{
	FRotator ControlRotation = GetControlRotation();
	FVector RightDirection = FRotationMatrix(FRotator(0.0f, ControlRotation.Yaw, 0.0f)).GetUnitAxis(EAxis::Y);

	AddMovementInput(RightDirection, Amount);
}

void ACOA_Avatar::RunPressed()
{
	if (!StaminaDrained)
	{
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
		IsRunning = true;
	}

}

void ACOA_Avatar::RunReleased()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	IsRunning = false;
}

void ACOA_Avatar::UpdateMovementParams()
{
	//GetCharacterMovement()
}
