// Fill out your copyright notice in the Description page of Project Settings.


#include "Humanoid.h"

// Sets default values
AHumanoid::AHumanoid()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
  MoveComp = GetCharacterMovement();
  MoveComp->SetComponentTickEnabled(true);
  MoveComp->SetActive(true);
  UE_LOG(LogTemp, Warning, TEXT("Constructor"));

}

// Called when the game starts or when spawned
void AHumanoid::BeginPlay() {
  UE_LOG(LogTemp, Warning, TEXT("Hello World %s"), *GetMesh()->GetName());
  // Weapon init
  if (WeaponClass) {
    UE_LOG(LogTemp, Warning, TEXT("Has weapon class"));
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    FVector SpawnLocation = FVector::ZeroVector;
    FRotator SpawnRotation = FRotator::ZeroRotator;
    Weapon = GetWorld()->SpawnActor<AWeapon>(
        WeaponClass, SpawnLocation, SpawnRotation, SpawnParams);

    if (Weapon) {
      UE_LOG(LogTemp, Warning, TEXT("Spawned the gun"));
      FName SocketName(TEXT("hand_gun"));
      Weapon->AttachToComponent(
          this->GetRootComponent(),
          FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
    }
    setWeaponState(WeaponClass);
  }
}

void AHumanoid::setWeaponState(TSubclassOf<AWeapon> NewWeapon) {
  UE_LOG(LogTemp, Warning, TEXT("Setting the weapon state"));
  if (Weapon) {
    WeaponState=Weapon->GetWeaponAnimState();
    UE_LOG(LogTemp, Warning, TEXT("Actually setting the weapon class"));
  }
}

// Called every frame
void AHumanoid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
