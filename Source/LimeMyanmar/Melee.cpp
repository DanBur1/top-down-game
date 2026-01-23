// Fill out your copyright notice in the Description page of Project Settings.

#include "Melee.h"

bool AMelee::attack() {
  UE_LOG(LogTemp, Warning, TEXT("Attack called"));
  if (can_swing)
    return swing();
  else
    return stab();
}

bool AMelee::stab() {
  if (!Wielder)
    return false;

  UWorld *World = GetWorld();
  if (!World)
    return false;
  UE_LOG(LogTemp, Warning, TEXT("Stab passed checks"));
  // Get poke location and direction
  FVector Start = Wielder->GetActorLocation();
  FVector Forward = Wielder->GetActorForwardVector();
  FVector End = Start + Forward * range;

  FCollisionQueryParams TraceParams;
  TraceParams.AddIgnoredActor(Wielder);

  // LineTrace till first non pawn
  FHitResult Hit;
  ECollisionChannel TraceChannel = ECC_WorldStatic;
  bool bHit = World->LineTraceSingleByObjectType(Hit, Start, End, TraceChannel,
                                        TraceParams);
  if (bHit)
    End = Hit.Location;

  TArray<FHitResult> ActorsHit;
  World->LineTraceMultiByChannel(ActorsHit, Start, End, ECC_Visibility, TraceParams);

  for (FHitResult &ActorHit : ActorsHit) {
    AActor *HitActor = ActorHit.GetActor();
    if (HitActor && HitActor != Wielder) {
      UGameplayStatics::ApplyDamage(HitActor, damage,
                                    Wielder->GetInstigatorController(),
                                    Wielder,
                                    nullptr);
      UE_LOG(LogTemp, Warning, TEXT("Melee hit %s"), *HitActor->GetName());
    }
  }

  DrawDebugLine(World, Start, End, FColor::Red, false, 2.f);

  return true;
}

bool AMelee::swing() {
  UE_LOG(LogTemp, Warning, TEXT("Swing called"));
  if (!Wielder)
    return false;

  UWorld *World = GetWorld();
  if (!World)
    return false;
  UE_LOG(LogTemp, Warning, TEXT("Swing passed checks"));
  FVector Start = Wielder->GetActorLocation();
  FVector Forward = Wielder->GetActorForwardVector();

  float HalfAngle = 75.0f;
  float SweepRadius = range;

  FCollisionShape SweepShape = FCollisionShape::MakeSphere(SweepRadius);

  TArray<FOverlapResult> OverlapResults;
  FCollisionQueryParams QueryParams;
  QueryParams.AddIgnoredActor(Wielder);
  QueryParams.bTraceComplex = false;

  FCollisionObjectQueryParams ObjectQueryParams(
      FCollisionObjectQueryParams::InitType::AllDynamicObjects);
  ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);
  ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

  bool bFoundActors = World->OverlapMultiByObjectType(
      OverlapResults, Start, FQuat::Identity, ObjectQueryParams, SweepShape,
      QueryParams);

  if (!bFoundActors)
    return true;
  UE_LOG(LogTemp, Warning, TEXT("Swing found actors"));
  TArray<AActor *> AlreadyHitActors;
  bool bHitAny = false;

  for (const FOverlapResult &Result : OverlapResults) {
    AActor *HitActor = Result.GetActor();

    if (!HitActor || HitActor == Wielder || AlreadyHitActors.Contains(HitActor))
      continue;

    FVector ToTarget = (HitActor->GetActorLocation() - Start).GetSafeNormal();
    float Dot = FVector::DotProduct(Forward, ToTarget);
    float Angle = FMath::RadiansToDegrees(FMath::Acos(Dot));

    if (Angle > HalfAngle)
      continue;

    FHitResult Hit;
    FVector End = HitActor->GetActorLocation();

    bool bObstructed = World->LineTraceSingleByChannel(
        Hit, Start, End,
        ECC_Visibility,
        QueryParams);

    if (bObstructed && Hit.GetActor() != HitActor)
      continue;

    UGameplayStatics::ApplyDamage(
        HitActor, damage, Wielder->GetInstigatorController(), Wielder, nullptr);

    AlreadyHitActors.Add(HitActor);
  }
    UE_LOG(LogTemp, Warning, TEXT("Swing finished"));
  return true;
}