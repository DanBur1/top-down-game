// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Bullet.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Gun.generated.h"

/**
 * 
 */
UCLASS()
class LIMEMYANMAR_API AGun : public AWeapon
{
	GENERATED_BODY()
public:
  // Properties

  // Number of ammunition stored in the weapon
  UPROPERTY(EditAnywhere, Category="Other")
  int magazine = 0;
	// Number of bullets spawned during one fire call
  UPROPERTY(EditAnywhere, Category = "Ballistics")
  int projectiles_per_shot = 1;
  // Max offset of the bullet trajectory from barrel direction
  UPROPERTY(EditAnywhere, Category = "Ballistics")
  float spread_angle = 0.f;

protected:

	// Default Unreal events

	// Constructor
	AGun();

	// Properties
	
	// Used to call bullet class during spawn
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ballistics")
  TSubclassOf<ABullet> BulletClass;
	// Component that is used to get gun's barrel muzzle location
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ballistics")
  USceneComponent *Muzzle;
  // Character who uses the gun
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Other")
  ACharacter *Gunman;

	// Methods

  // Override of Weapons attack function
	bool attack() override;
	// Actual attack function of guns
  bool fire();
};
