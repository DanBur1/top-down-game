// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

AGun::AGun(){
  Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
  Muzzle->SetupAttachment(RootComponent);
}

void AGun::BeginPlay() {
  Super::BeginPlay();
  if (GetOwner())
    Gunman = Cast<ACharacter>(GetOwner());
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
    UE_LOG(LogTemp, Warning, TEXT("Spawn location %s"), *SpawnLocation.ToString());
    // Deffered spawn to modify the bullet before it's activated
    ABullet *SpawnedBullet = GetWorld()->SpawnActorDeferred<ABullet>(
        BulletClass, FTransform(SpawnRotation, SpawnLocation, FVector(1.f, 1.f, 1.f)), nullptr, nullptr,
        ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
    if (!SpawnedBullet) {
      fail_rate++;
      continue;
    } else if (Gunman) {
      // Setting the bullet up
      SpawnedBullet->damage = damage;
      SpawnedBullet->speed_of_gun =
            Gunman->GetMovementComponent()->Velocity.Length();
      SpawnedBullet->BarrelDirection = NewDirection.GetSafeNormal();
      SpawnedBullet->Owner = Gunman;
      Gunman->GetMesh()->IgnoreActorWhenMoving(SpawnedBullet, true);
      // Spawn bullet
      UGameplayStatics::FinishSpawningActor(
          SpawnedBullet, FTransform(SpawnRotation, SpawnLocation, FVector(1.f, 1.f, 1.f)));
    }
  }
  UE_LOG(LogTemp, Warning, TEXT("%d bullets not spawned"), fail_rate);
  return fail_rate<projectiles_per_shot;
}