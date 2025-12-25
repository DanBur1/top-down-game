// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrownWeapon.h"

// Sets default values
AThrownWeapon::AThrownWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
  ProjMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
  ProjMovement->RegisterComponent();
  ProjMovement->SetActive(false);
}

// Called when the game starts or when spawned
void AThrownWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AThrownWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AThrownWeapon::launch() {
  ProjMovement->MaxSpeed = 3000.f;
  ProjMovement->bRotationFollowsVelocity = true;
  ProjMovement->ProjectileGravityScale = 1.0f;
  if (GetOwner()) {
    ProjMovement->Velocity = GetOwner()->GetVelocity() * 100.f;
  } else {
    ProjMovement->Velocity = GetActorForwardVector() * 100.f;
  }
  ProjMovement->SetActive(true);
}