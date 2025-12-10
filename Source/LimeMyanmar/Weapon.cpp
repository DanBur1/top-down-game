// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
  // Visual
  WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
  RootComponent = WeaponMesh;
  WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
  WeaponMesh->SetCollisionObjectType(ECC_WorldDynamic);
  WeaponMesh->SetCollisionResponseToAllChannels(
      ECR_Ignore);
  WeaponMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel2,
                                            ECR_Block);
  WeaponMesh->SetSimulatePhysics(false);
  // WeaponMesh->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AWeapon::attack(){ return false; }

bool AWeapon::useWeapon(){
  if (is_cooling_down)
    return false;
  if (attack()) {
    is_cooling_down = true;
    GetWorldTimerManager().SetTimer(AttackCooldownTimer, this,
                                    &AWeapon::onCooldownFinished, cooldown,
                                    false);
    AnimState = EHumanoidArmStates::attacking;
    return true;
  } else return false;
}

void AWeapon::onCooldownFinished() {
  is_cooling_down = false;
  AnimState = EHumanoidArmStates::null;
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

