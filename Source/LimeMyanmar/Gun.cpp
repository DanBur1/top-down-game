// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

AGun::AGun(){
  Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
  Muzzle->SetupAttachment(RootComponent);
}

void AGun::BeginPlay() {
  Super::BeginPlay();
  if (GetOwner())
    Wielder = Cast<ACharacter>(GetOwner());
}

bool AGun::attack(){
  if (magazine>0) {
    magazine--;
    return fire();
  }
  return false;
}

bool AGun::fire() {
  if (!Muzzle || !BulletClass || !Wielder) {
    return false;
  }

  // Get barrel location and direction
  FVector SpawnLocation = Muzzle->GetComponentLocation();
  FVector Forward = Muzzle->GetForwardVector();
  int fail_rate = 0;

  // Array for spawned bullets
  TArray<ABullet *> SpawnedBullets;

  // Looping the creation of each projectile
  for (int i = 0; i < projectiles_per_shot; i++) {
    float HalfRad = FMath::DegreesToRadians(spread_angle * 0.5f);
    float RandomAngle = FMath::RandRange(-HalfRad, HalfRad);
    FVector NewDirection = Forward.RotateAngleAxis(
        FMath::RadiansToDegrees(RandomAngle), FVector::UpVector);

    FRotator SpawnRotation = NewDirection.Rotation();

    // Bullet spawn
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = Wielder;
    SpawnParams.Instigator = Wielder;
    SpawnParams.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    ABullet *SpawnedBullet = GetWorld()->SpawnActor<ABullet>(
        BulletClass, SpawnLocation, SpawnRotation, SpawnParams);

    if (!SpawnedBullet) {
      fail_rate++;
      continue;
    }

    // Bullet setup
    SpawnedBullet->damage = damage;
    SpawnedBullet->speed_of_gun = Wielder->GetVelocity().Size();
    SpawnedBullet->BarrelDirection = NewDirection;
    SpawnedBullet->Owner = Wielder;

    SpawnedBullets.Add(SpawnedBullet);
  }

  // Ignore collisions
  if (projectiles_per_shot > 1) {
    for (int i = 0; i < SpawnedBullets.Num(); i++) {
      if (!SpawnedBullets[i])
        continue;

      for (int j = 0; j < SpawnedBullets.Num(); j++) {
        if (i == j || !SpawnedBullets[j])
          continue;

        // Ignoring all bullets spawned by the same shot
        // Allows to pevent ricochet without removing bullet collisions
        // Which in turn allows to shoot down enemy bullets
        SpawnedBullets[i]->BulletMesh->IgnoreActorWhenMoving(SpawnedBullets[j],
                                                             true);
      }
    }
  }

  return fail_rate < projectiles_per_shot;
}