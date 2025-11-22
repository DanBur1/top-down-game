// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapon.h"
#include "Humanoid.generated.h"



UCLASS()
class LIMEMYANMAR_API AHumanoid : public ACharacter
{
	GENERATED_BODY()

protected:
  // Default Unreal events
	
	// Called when the game starts or when spawned
  virtual void BeginPlay() override;

  // Methods

  // Changes the weapon state to fit the animation
  void setWeaponState(TSubclassOf<AWeapon> NewWeapon);

public:
	// Default Unreal events

	// Sets default values for this character's properties
	AHumanoid();
	// Called every frame
  virtual void Tick(float DeltaTime) override;

	// Properties

  // Enum that is used to store character's state depending on arm movement
  UPROPERTY(EditAnywhere, Category = "Character states")
  EHumanoidArmStates ArmState = EHumanoidArmStates::null;
  // Enum that is used to store character's state depending on movement
  UPROPERTY(EditAnywhere,  Category = "Character states")
  EHumanoidBodyStates BodyState = EHumanoidBodyStates::idle;
  // Enum that is used to store character's state depending on his weapon
  UPROPERTY(EditAnywhere, Category = "Character states")
  EHumanoidWeaponStates WeaponState = EHumanoidWeaponStates::unarmed;
	// Movement component
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
  UCharacterMovementComponent *MoveComp;
  // Weapon that character starts with
  UPROPERTY(EditAnywhere, Category = "Weapons")
  TSubclassOf<AWeapon> WeaponClass;
	// Weapon character can use
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapons")
  AWeapon *Weapon;
};
