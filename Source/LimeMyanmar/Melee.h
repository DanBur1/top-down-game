// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Melee.generated.h"

/**
 * 
 */
UCLASS()
class LIMEMYANMAR_API AMelee : public AWeapon
{
	GENERATED_BODY()
protected:
	// Properties

	// If true the weapon swings if false the weapon pokes
  bool can_swing = false;
  // Either the length of the melee weapon or the distance a gun can shoot at
  UPROPERTY(EditAnywhere, Category = "Weapon parameters")
  float range = 0.f;

	// Methods

	// Override of weapon attack function
  bool attack() override;
	// Scans for actors in front of the attacking character and deals damage to them
  bool poke();
	// Scans for actors within certain sector around attacking character and deals damage to them
	bool swing();

};
