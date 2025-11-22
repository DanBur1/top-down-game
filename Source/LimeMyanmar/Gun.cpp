// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

AGun::AGun(){
  if (GetOwner())
    Gunman = Cast<ACharacter>(GetOwner());
  Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
  Muzzle->SetupAttachment(RootComponent);
}

bool AGun::attack(){
  return fire();
}

bool AGun::fire(){
  if (!Muzzle || !BulletClass) {
    return false;
  }
  
  // Get barrel location and direction
  FVector SpawnLocation = Muzzle->GetComponentLocation();
  FVector Forward = Muzzle->GetForwardVector();
  
  // Int used to count failed spawns. fire only fails when all bullets failed to spawn
  int fail_rate = 0;

  // Running a spawn function for each bullet a gun can fire per shot
  for (int i = 0; i < projectiles_per_shot; i++) {

    // Calculating bullet trajectory considering the offset
    float HalfRad = FMath::DegreesToRadians(spread_angle * 0.5f);
    float RandomAngle = FMath::RandRange(-HalfRad, HalfRad);
    FVector NewDirection = Forward.RotateAngleAxis(
        FMath::RadiansToDegrees(RandomAngle), FVector::UpVector);
    FRotator SpawnRotation = NewDirection.Rotation();

    // Deffered spawn to modify the bullet before it's activated
    ABullet *SpawnedBullet = GetWorld()->SpawnActorDeferred<ABullet>(
        BulletClass, FTransform(SpawnRotation, SpawnLocation), nullptr, nullptr,
        ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
    if (!SpawnedBullet) {
      fail_rate++;
      continue;
    }

    // Setting the bullet up
    SpawnedBullet->damage = damage;
    SpawnedBullet->speed_of_gun =
        Gunman->GetMovementComponent()->Velocity.Length();

    // Spawn bullet
    SpawnedBullet->FinishSpawning(FTransform(SpawnRotation, SpawnLocation));
  }
  return fail_rate<projectiles_per_shot;
}