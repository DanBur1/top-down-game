// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectEnums.h"
#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Weapon.generated.h"

UCLASS()
class LIMEMYANMAR_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Unreal default events

	// Constructor
	AWeapon();

	// Properties
  
  // Animation state associated with that weapon type
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon parameters")
  EHumanoidWeaponStates AnimType = EHumanoidWeaponStates::unarmed;
  // Animation state for the current action of the weapon
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon parameters")
  EHumanoidArmStates AnimState = EHumanoidArmStates::null;
  // Time it takes to reset the weapon
  UPROPERTY(EditAnywhere, Category = "Weapon parameters")
  float cooldown = 0.f;
  // Amount of damage dealt by a single attack of the weapon
  UPROPERTY(EditAnywhere, Category = "Weapon parameters")
  float damage = 0.f;
  // Mesh
  UPROPERTY(VisibleAnywhere, Category = "Components")
  UStaticMeshComponent *WeaponMesh;
  // Character wielding the weapon
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Other")
  ACharacter *Wielder;

  // Called every frame
  virtual void Tick(float DeltaTime) override;

  // Methods

  // Called when attack starts
  void startAttacking();
  // Called when attack ends
  void stopAttacking();
  // Calls attack for weapon children without cooldown
  void useWeaponAuto();
  // Calls attack for weapon children with cooldown
  void useWeaponSemi();


protected:
	// Unreal default events
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Properties

  // Timer used for cooldown of the weapons
  UPROPERTY()
  FTimerHandle AttackCooldownTimer;
  // Flag that is set true when the cooldown time starts and false if it passed
  UPROPERTY()
  bool is_cooling_down=false;
  // Flag that is used to check whether the weapon should call attack on timer or on button push
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon parameters")
  bool is_automatic = false;
	// Methods

	// Attack function. Returns false if it's impossible
  UFUNCTION()
  virtual bool attack();
	// Switches is_cooling_down to false
  UFUNCTION()
  void onCooldownFinished();

};
