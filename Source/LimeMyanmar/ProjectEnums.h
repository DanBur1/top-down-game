#pragma once

#include "CoreMinimal.h"

// Enumerations

UENUM(BlueprintType)
// States that affect character's upper body animations
enum class EHumanoidArmStates : uint8 {
  null UMETA(DisplayName = "Default state"), // default state
  interacting UMETA(
      DisplayName = "Interacting"), // character interacting with interactables
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
  unarmed UMETA(DisplayName = "Unarmed"), // BP_Unarmed
  handgun UMETA(DisplayName = "Handgun"), // BP_Handgun
  cold_short UMETA(DisplayName = "Cold Short"),
  cold_long UMETA(DisplayName = "Cold Long"),
  pump UMETA(DisplayName = "Pump"),
  rifle UMETA(DisplayName = "Rifle"),
  throwable UMETA(DisplayName = "Throwable")
};

UENUM(BlueprintType)
// Enumeration of all teams in the game. Used to distinguish between friendlies
// and hostiles. Made via a enum in case i'll want to add more than 2
enum class ETeams : uint8{
  humans UMETA(DisplayName = "Human Team"), // Player friendly
  aliens UMETA(DisplayName = "Alien Team") // Player hostile
};