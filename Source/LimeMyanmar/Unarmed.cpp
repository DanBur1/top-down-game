// Fill out your copyright notice in the Description page of Project Settings.


#include "Unarmed.h"

AUnarmed::AUnarmed() {
  range = 100.f;
  AnimType = EHumanoidWeaponStates::unarmed;
  AnimState = EHumanoidArmStates::null;
  cooldown = 0.2f;
  damage = 100.f;
}