// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Bullet.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapon.h"
#include "BrokenShotgun.generated.h"

/**
 *
 */
UCLASS()
class LIMEMYANMAR_API ABrokenShotgun : public AWeapon {
  GENERATED_BODY()
public:
  // Defaul Unreal events

  // Begin play
  virtual void BeginPlay() override;
  // Properties

  // Number of ammunition stored in the weapon
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Other")
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
  ABrokenShotgun();

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
