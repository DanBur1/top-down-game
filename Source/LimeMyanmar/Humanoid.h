// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DestructableComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Gun.h"
#include "Melee.h"
#include "Humanoid.generated.h"



UCLASS()
class LIMEMYANMAR_API AHumanoid : public ACharacter
{
	GENERATED_BODY()
private:

  // Methods

  // Used to quickly decide on what weapon should a character pick if several are availiable
  int weaponPriority(AWeapon *Weapon);

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
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character states")
  EHumanoidArmStates ArmState = EHumanoidArmStates::null;
  // Enum that is used to store character's state depending on movement
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character states")
  EHumanoidBodyStates BodyState = EHumanoidBodyStates::idle;
  // Enum that is used to store character's state depending on his weapon
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character states")
  EHumanoidWeaponStates WeaponState = EHumanoidWeaponStates::unarmed;
  // Component responsible for health and death
  UPROPERTY(EditAnywhere, Category = "Others")
  UDestructableComponent *HealthSystem;
	// Movement component
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
  UCharacterMovementComponent *MoveComp;
  // Class of the weapon character uses. Can be used to set starter weapon
  UPROPERTY(EditAnywhere, Category = "Weapons")
  TSubclassOf<AWeapon> WeaponClass;
	// Weapon character can use
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapons")
  AWeapon *Weapon;

  // Methods

  // Picks up closest weapon (or switches to unarmed if there's none) and throws the previous one
  void replaceWeapon(float SearchRadius = 200.f);
  // Uses current character weapon as projectile
  void throwWeapon();
  // Calls attack function in the weapon
  void useCharacterWeapon();
};
