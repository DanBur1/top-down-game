// Fill out your copyright notice in the Description page of Project Settings.


#include "Humanoid.h"

// Sets default values
AHumanoid::AHumanoid()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  // Movement
  MoveComp = GetCharacterMovement();
  MoveComp->SetComponentTickEnabled(true);
  MoveComp->SetActive(true);
  UE_LOG(LogTemp, Warning, TEXT("Constructor"));

  // Health
  HealthSystem =
      CreateDefaultSubobject<UDestructableComponent>(TEXT("Health"));
}

int AHumanoid::weaponPriority(AWeapon *TestedWeapon){
  if (!TestedWeapon)
    return 0;
  AGun *AsGun = Cast<AGun>(TestedWeapon);
  if (AsGun)
    return 1*AsGun->magazine;
  if (Cast<AMelee>(TestedWeapon))
    return 2;
  return 0;
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
          this->GetMesh(),
          FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
    }
  }
}


void AHumanoid::replaceWeapon(float SearchRadius) {
  if (Weapon)
    throwWeapon();
  UWorld *World = GetWorld();
  if (!World)
    return;
  TArray<FHitResult> HitResults;
  FVector Center = GetActorLocation();

  FCollisionQueryParams QueryParams;
  QueryParams.AddIgnoredActor(this);

  bool bHit = World->SweepMultiByChannel(
      HitResults, Center, Center, FQuat::Identity, ECC_GameTraceChannel2,
      FCollisionShape::MakeSphere(SearchRadius), QueryParams);
  UE_LOG(LogTemp, Warning, TEXT("I'M %d PICKING"), bHit);
  UE_LOG(LogTemp, Warning, TEXT("FOUND %d ACTORS"), HitResults.Num());
  if (!bHit || HitResults.Num() == 0) {
    UE_LOG(LogTemp, Warning, TEXT("No weapons found nearby"));
    return;
  }

  TArray<AWeapon *> NearbyWeapons;
  for (FHitResult &Hit : HitResults) {
    UE_LOG(LogTemp, Warning, TEXT("FOUND %s"), *Hit.GetActor()->GetName());
    AWeapon *AvailableWeapon = Cast<AWeapon>(Hit.GetActor());
    if ((AvailableWeapon) && (AvailableWeapon != Weapon)) {
      NearbyWeapons.Add(AvailableWeapon);
    }
  }
  UE_LOG(LogTemp, Warning, TEXT("FOUND %d WEAPONS"), NearbyWeapons.Num());
  if (NearbyWeapons.Num() == 0)
    return;

  AWeapon *BestWeapon = nullptr;
  int32 HighestPriority = -1;

  for (AWeapon *AvailableWeapon : NearbyWeapons) {
    int32 Priority = weaponPriority(AvailableWeapon);
    if (Priority > HighestPriority) {
      HighestPriority = Priority;
      BestWeapon = AvailableWeapon;
      UE_LOG(LogTemp, Warning, TEXT("Probably not here"));
    }
  }

  if (BestWeapon) {
    Weapon = BestWeapon;
    WeaponClass = BestWeapon->GetClass();
    FName SocketName(TEXT("hand_gun"));
    Weapon->AttachToComponent(
        this->GetMesh(),
        FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
    UE_LOG(LogTemp, Warning, TEXT("God i hope not here it's basic as fuck"), HitResults.Num());
  }
}

void AHumanoid::throwWeapon(){

}

void AHumanoid::useCharacterWeapon(){
  if (Weapon)
    Weapon->useWeapon();
}

// Called every frame
void AHumanoid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
