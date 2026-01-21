// Fill out your copyright notice in the Description page of Project Settings.

#include "Melee.h"

bool AMelee::attack() {
  if (can_swing)
    return swing();
  else
    return stab();
}

bool AMelee::stab() {
  if (!Owner)
    return false;

  UWorld *World = GetWorld();
  if (!World)
    return false;

  // Get poke location and direction
  FVector Start = Owner->GetActorLocation();
  FVector Forward = Owner->GetActorForwardVector();
  FVector End = Start + Forward * range;

  FCollisionQueryParams TraceParams;
  TraceParams.AddIgnoredActor(Owner);


  FHitResult Hit;
  bool bHit = World->LineTraceSingleByChannel(Hit, Start, End,
                                                  ECC_Visibility, TraceParams);
  AActor * OtherActor= Hit.GetActor();
  if (OtherActor) {
    UGameplayStatics::ApplyDamage(OtherActor, damage, GetInstigatorController(),
                                  GetOwner(), nullptr);
    UE_LOG(LogTemp, Warning, TEXT("Hit a %s"), *OtherActor->GetName());
  }
  return true;
}

bool AMelee::swing() {
  // hot' by nikakoi programmator ne zashel na etu vetku i ne uvidel kak ubogo
  // ya pomechau mesta gde eshe net koda
  return false;
}