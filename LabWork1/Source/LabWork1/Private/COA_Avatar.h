// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "COABaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "COA_Avatar.generated.h"

/**
 * 
 */
UCLASS()
class ACOA_Avatar : public ACOABaseCharacter
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;


public:

	ACOA_Avatar();
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditAnywhere, Category = "COA")
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = "COA")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
	float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
	float StaminaGainRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
	float StaminaDrainRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
	bool StaminaDrained;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
	bool IsRunning;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
	float RunSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
	bool HoldingRunKey;



private:

	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void RunPressed();
	void RunReleased();

	void UpdateMovementParams();
};
