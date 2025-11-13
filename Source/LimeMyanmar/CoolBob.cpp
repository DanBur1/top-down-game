// Fill out your copyright notice in the Description page of Project Settings.


#include "CoolBob.h"

void ACoolBob::move(float x, float y){
  AddMovementInput(FVector(x, y, 0.f), 1.f);
}