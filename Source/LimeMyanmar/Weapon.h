// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HumanoidAnimationStates.h"
#include "GameFramework/Actor.h"
#include "HumanoidAnimationStates.h"
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

	// Animation state associated with that weapon
  UPROPERTY(EditAnywhere, Category = "Weapon parameters")
  EHumanoidWeaponStates AnimState = EHumanoidWeaponStates::unarmed;
  // Time it takes to reset the weapon
  UPROPERTY(EditAnywhere, Category = "Weapon parameters")
  float cooldown = 0.f;
  // Amount of damage dealt by a single attack of the weapon
  UPROPERTY(EditAnywhere, Category = "Weapon parameters")
  float damage = 0.f;

	// Methods

	// Allows character class to quickly get the fitting anim state for the weapon
  UFUNCTION( BlueprintCallable, Category = "Weapon")
  EHumanoidWeaponStates GetWeaponAnimState();

protected:
	// Unreal default events
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Properties

	// Time of the last attack
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Parameters")
  float last_attack = 0.f;
	// Mesh
  UPROPERTY(VisibleAnywhere, Category = "Components")
  UStaticMeshComponent *WeaponMesh;

	// Methods

	// Attack function. Returns false if it's impossible
  virtual bool attack();
	// Checks whether the weapon is still in cooldown stage
  bool isCoolingDown();
	// Calls attack for weapon children
  bool useWeapon();

public:	
	// Unreal default events
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
