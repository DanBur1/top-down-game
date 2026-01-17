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
  if (!Muzzle || !BulletClass) {
    return false;
  }

  // Get barrel location and direction
  FVector BaseLocation = Muzzle->GetComponentLocation();
  FVector Forward = Muzzle->GetForwardVector();
  int fail_rate = 0;

  // Создаем массив для временного хранения пуль
  TArray<ABullet *> BulletsToSpawn;

  for (int i = 0; i < projectiles_per_shot; i++) {
    float HalfRad = FMath::DegreesToRadians(spread_angle * 0.5f);
    float RandomAngle = FMath::RandRange(-HalfRad, HalfRad);
    FVector NewDirection = Forward.RotateAngleAxis(
        FMath::RadiansToDegrees(RandomAngle), FVector::UpVector);

    // Немного смещаем точку спавна для каждой пули
    FVector SpawnOffset = FVector(0, 0, 0);
    if (projectiles_per_shot > 1) {
      float OffsetAmount = 5.0f; // Небольшое смещение
      SpawnOffset = FVector(FMath::RandRange(-OffsetAmount, OffsetAmount),
                            FMath::RandRange(-OffsetAmount, OffsetAmount), 0);
    }

    FVector SpawnLocation = BaseLocation + SpawnOffset;
    FRotator SpawnRotation = NewDirection.Rotation();
    ABullet *SpawnedBullet = GetWorld()->SpawnActorDeferred<ABullet>(
        BulletClass, FTransform(SpawnRotation, SpawnLocation), nullptr, nullptr,
        ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

    if (!SpawnedBullet) {
      fail_rate++;
      continue;
    }

    BulletsToSpawn.Add(SpawnedBullet);
  }

  // Finishing the spawn
  for (ABullet *Bullet : BulletsToSpawn) {
    UE_LOG(LogTemp, Warning, TEXT("HERE 0"));
    if (Wielder) {
      UE_LOG(LogTemp, Warning, TEXT("HERE %s"), *Wielder->GetName());
      // Adding ignored actors
      Bullet->BulletMesh->IgnoreActorWhenMoving(this, true);
      for (TActorIterator<ABullet> It(GetWorld()); It; ++It) {
        if (It->GetOwner() == Wielder && *It != Bullet) {
          UE_LOG(LogTemp, Warning, TEXT("HERE 1"));
          Bullet->BulletMesh->IgnoreActorWhenMoving(*It, true);
        }
      }


      // Bullet setup
      Bullet->damage = damage;
      Bullet->speed_of_gun = Wielder->GetVelocity().Size();
      Bullet->BarrelDirection = Bullet->GetActorForwardVector();
      Bullet->Owner = Wielder;
      Bullet->SetInstigator(Wielder);

      // Spawning
      UGameplayStatics::FinishSpawningActor(Bullet, Bullet->GetTransform());
    }
  }

  return fail_rate < projectiles_per_shot;
}