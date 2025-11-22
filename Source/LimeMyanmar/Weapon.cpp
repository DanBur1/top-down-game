// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
  // Visual
  WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
  RootComponent = WeaponMesh;
}

EHumanoidWeaponStates AWeapon::GetWeaponAnimState(){ return AnimState; }

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AWeapon::attack(){ return false; }

bool AWeapon::isCoolingDown(){
  float CurrentTime = GetWorld()->GetTimeSeconds();
  return (CurrentTime - last_attack) < cooldown;
}

bool AWeapon::useWeapon(){
  if (isCoolingDown())
    return false;
  last_attack = GetWorld()->GetTimeSeconds();
  return attack();
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

