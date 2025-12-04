// Fill out your copyright notice in the Description page of Project Settings.


#include "Melee.h"

bool AMelee::attack(){ AWeapon::attack();
  if (can_swing)
    return swing();
  else
    return poke();
}

bool AMelee::poke(){
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

  // LineTrace till first non pawn
  FHitResult Hit;
  ECollisionChannel TraceChannel = ECC_Visibility;
  bool bHit = World->LineTraceSingleByChannel(Hit, Start, End, TraceChannel,
                                              TraceParams);

  if (bHit) {
    End = Hit.Location; // Останавливаемся на препятствии

    // Собираем всех Pawn'ов на пути трассировки
    TArray<FHitResult> PawnsHit;
    World->LineTraceMultiByChannel(PawnsHit, Start, End, ECC_Pawn, TraceParams);

    // Наносим урон всем Pawn'ам кроме владельца
    for (FHitResult &PawnHit : PawnsHit) {
      APawn *HitPawn = Cast<APawn>(PawnHit.GetActor());
      if (HitPawn && HitPawn != Owner) {
        UGameplayStatics::ApplyDamage(
            HitPawn, damage, Owner->GetInstigatorController(), Owner, nullptr);
        UE_LOG(LogTemp, Warning, TEXT("Melee hit %s"), *HitPawn->GetName());
      }
    }

    // Debug линия
    DrawDebugLine(World, Start, End, FColor::Red, false, 2.f);
    return true;
  }

  return false;
}

bool AMelee::swing(){
  // hot' by nikakoi programmator ne zashel na etu vetku i ne uvidel kak ubogo ya pomechau mesta gde eshe net koda
  return false;
}