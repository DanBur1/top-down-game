// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Humanoid.generated.h"

UCLASS()
class LIMEMYANMAR_API AHumanoid : public ACharacter
{
	GENERATED_BODY()

public:
	// Default Unreal events

	// Sets default values for this character's properties
	AHumanoid();
	// Called every frame
  virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
  virtual void SetupPlayerInputComponent(
  class UInputComponent *PlayerInputComponent) override;

	// Properties

	// Mesh reference used to access it in code
	USkeletalMeshComponent *MeshComp;
	// Weapon character can use

	// Movement component
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
  UCharacterMovementComponent *MoveComp;

	protected:
	// Default Unreal events
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
