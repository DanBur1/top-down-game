// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectEnums.h"
#include "GameFramework/Actor.h"
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

  // Time it takes to reset the weapon
  UPROPERTY(EditAnywhere, Category = "Weapon parameters")
  float cooldown = 0.f;
  // Amount of damage dealt by a single attack of the weapon
  UPROPERTY(EditAnywhere, Category = "Weapon parameters")
  float damage = 0.f;

	// Methods

	// Allows other classes to quickly get the animation state associated with this weapon type
  UFUNCTION( BlueprintCallable, Category = "Weapon")
  EHumanoidWeaponStates GetWeaponType();
  // Allows other classes to get the state this weapon is in
  UFUNCTION(BlueprintCallable, Category = "Weapon")
  EHumanoidArmStates GetWeaponState();

protected:
	// Unreal default events
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Properties

  // Animation state associated with that weapon type
  UPROPERTY(EditAnywhere, Category = "Weapon parameters")
  EHumanoidWeaponStates AnimType = EHumanoidWeaponStates::unarmed;
  // Animation state for the current action of the weapon
  UPROPERTY(EditAnywhere, Category = "Weapon parameters")
  EHumanoidArmStates AnimState = EHumanoidArmStates::null;
  // Timer used for cooldown of the weapons
  UPROPERTY()
  FTimerHandle AttackCooldownTimer;
  // Flag that is set true when the cooldown time starts and false if it passed
  UPROPERTY()
  bool is_cooling_down=false;
	// Mesh
  UPROPERTY(VisibleAnywhere, Category = "Components")
  UStaticMeshComponent *WeaponMesh;

	// Methods

	// Attack function. Returns false if it's impossible
  virtual bool attack();
	// Switches is_cooling_down to false
  UFUNCTION()
  void onCooldownFinished();

public:	
	// Unreal default events
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Methods
  
	// Calls attack for weapon children
  bool useWeapon();
};
