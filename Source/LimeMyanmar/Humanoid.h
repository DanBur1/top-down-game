// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Humanoid.generated.h"

 // Enumerations

UENUM(BlueprintType)
// States that affect character's upper body animations
enum class EHumanoidArmStates : uint8 {
  null UMETA(DisplayName = "Default state"), // default state
  interacting UMETA(
      DisplayName =
          "Interacting"), // character is interacting with interactables
  attacking UMETA(DisplayName = "Attacking"), // character uses weapon
  picking UMETA(DisplayName = "Picking"),     // character picks an item
  throwing UMETA(DisplayName = "Throwing")
};

UENUM(BlueprintType)
// State that defines animations of the rest of the body
enum class EHumanoidBodyStates : uint8 {
  idle UMETA(DisplayName = "Idle"),     // default state
  moving UMETA(DisplayName = "Moving"), // character is walking
  unconscious UMETA(DisplayName =
                        "Unconscious"),    // character fell but still alive
  dying UMETA(DisplayName = "Dying"),      // character is dead
  finisher UMETA(DisplayName = "Finisher") // character is killing downed enemy
};

UENUM(BlueprintType)
// State that affects the arm position of the character
enum class EHumanoidWeaponStates : uint8 {
  unarmed UMETA(DisplayName = "Unarmed"),
  handgun UMETA(DisplayName = "Handgun"),
  cold_short UMETA(DisplayName = "Cold Short"),
  cold_long UMETA(DisplayName = "Cold Long"),
  pump UMETA(DisplayName = "Pump"),
  rifle UMETA(DisplayName = "Rifle"),
  throwable UMETA(DisplayName = "Throwable")
};

UCLASS()
class LIMEMYANMAR_API AHumanoid : public ACharacter
{
	GENERATED_BODY()

protected:
  // Default Unreal events
	
	// Called when the game starts or when spawned
  virtual void BeginPlay() override;


public:
	// Default Unreal events

	// Sets default values for this character's properties
	AHumanoid();
	// Called every frame
  virtual void Tick(float DeltaTime) override;

	// Properties

	// Movement component
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
  UCharacterMovementComponent *MoveComp;
  // Enum that is used to store character's state depending on arm movement
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character states")
  EHumanoidArmStates ArmState = EHumanoidArmStates::null;
	// Enum that is used to store character's state depending on movement
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character states")
  EHumanoidBodyStates BodyState = EHumanoidBodyStates::idle;
	// Enum that is used to store character's state depending on his weapon
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character states")
  EHumanoidWeaponStates WeaponState = EHumanoidWeaponStates::unarmed;
	// Weapon character can use

};
