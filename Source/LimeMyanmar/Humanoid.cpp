// Fill out your copyright notice in the Description page of Project Settings.


#include "Humanoid.h"

// Sets default values
AHumanoid::AHumanoid()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  UE_LOG(LogTemp, Warning, TEXT("Constructor"));

  // Health
  HealthSystem =
      CreateDefaultSubobject<UDestructableComponent>(TEXT("Health"));

  Weapon = nullptr;
  Fists = nullptr;
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
  Super::BeginPlay();
  UE_LOG(LogTemp, Warning, TEXT("Hello World %s"), *GetMesh()->GetName());

    // Movement
  MoveComp = GetCharacterMovement();
  if (MoveComp) {
    MoveComp->SetComponentTickEnabled(true);
    MoveComp->SetActive(true);
  }

  // Weapon init
  FActorSpawnParameters SpawnParams;
  SpawnParams.Owner = this;
  SpawnParams.SpawnCollisionHandlingOverride =
      ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
  FVector SpawnLocation = FVector::ZeroVector;
  FRotator SpawnRotation = FRotator::ZeroRotator;
  Fists = GetWorld()->SpawnActor<AUnarmed>(
      AUnarmed::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
  if (WeaponClass) {
    UE_LOG(LogTemp, Warning, TEXT("Has weapon class"));
    Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass, SpawnLocation,
                                             SpawnRotation, SpawnParams);

    if (Weapon) {
      UE_LOG(LogTemp, Warning, TEXT("Spawned the gun"));
      FName SocketName(TEXT("hand_gun"));
      Weapon->AttachToComponent(
          this->GetMesh(),
          FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
    }
  } else
    Weapon = Fists;

  // Connecting the events

  // Death
  if (HealthSystem) {
    HealthSystem->OnDeath.AddDynamic(this, &AHumanoid::death);
  }
}

void AHumanoid::death(){ GetController()->UnPossess();
}

void AHumanoid::replaceWeapon(float SearchRadius) {
  UE_LOG(LogTemp, Error, TEXT("REPLACE CALLED - Current Weapon: %s"),
         Weapon ? *Weapon->GetName() : TEXT("NULL"));

  // If character already has a weapon and it's not his own hands throw it out
  if ((Weapon)&&(!Weapon->IsA(AUnarmed::StaticClass())))
    throwWeapon();
  // Checking if pointer to world is valid so it doesn't crash later during collision check
  UWorld *World = GetWorld();
  if (!World)
    return;

  // Preparing for collision check
  TArray<FHitResult> HitResults;
  FVector Center = GetActorLocation();
  FCollisionQueryParams QueryParams;
  QueryParams.AddIgnoredActor(this);
  QueryParams.AddIgnoredActor(Weapon);
  
  // Collision check to find any weapons in overlapped area
  bool bHit = World->SweepMultiByChannel(
      HitResults, Center, Center, FQuat::Identity, ECC_GameTraceChannel2, // Custom channel for weapons
      FCollisionShape::MakeSphere(SearchRadius), QueryParams);
  UE_LOG(LogTemp, Warning, TEXT("I'M %d PICKING"), bHit);
  UE_LOG(LogTemp, Warning, TEXT("FOUND %d ACTORS"), HitResults.Num());
  if (!bHit || HitResults.Num() == 0) {
    UE_LOG(LogTemp, Warning, TEXT("No weapons found nearby"));
    return;
  }
  
  // Get weapons out of all overlapped actors responding to the collision check
  TArray<AWeapon *> NearbyWeapons;
  for (FHitResult &Hit : HitResults) {
    UE_LOG(LogTemp, Warning, TEXT("FOUND %s"), *Hit.GetActor()->GetName());
    AWeapon *AvailableWeapon = Cast<AWeapon>(Hit.GetActor());
    if ((AvailableWeapon)) {
      NearbyWeapons.Add(AvailableWeapon);
    }
  }
  UE_LOG(LogTemp, Warning, TEXT("FOUND %d WEAPONS"), NearbyWeapons.Num());
  if (NearbyWeapons.Num() == 0)
    return;

  // Pick weapon based on its priority
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

  // Attaching the weapon
  if (BestWeapon) {
    Weapon = BestWeapon;
    WeaponClass = BestWeapon->GetClass();
    FName SocketName(TEXT("hand_gun"));
    Weapon->AttachToComponent(
        this->GetMesh(),
        FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
    Weapon->Wielder = this;
  }
}

void AHumanoid::stopUsingWeapon(){
  if (Weapon){
    Weapon->stopAttacking();
  }
}

void AHumanoid::throwWeapon(){
  // You can't throw your fists away or a nonexisting weapon
  if (!Weapon || Weapon->IsA(AUnarmed::StaticClass()))
    return;

  // Getting the spawn data for the projectile that will replace the weapon during throw
  FVector SpawnLocation = Weapon->GetActorLocation();
  FRotator SpawnRotation = Weapon->GetActorRotation();
  FActorSpawnParameters SpawnParams;
  SpawnParams.SpawnCollisionHandlingOverride =
      ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

  // Spawn the projectile
  AThrownWeapon *ThrownWeapon = GetWorld()->SpawnActor<AThrownWeapon>(
      AThrownWeapon::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);

  if (ThrownWeapon) {
    ThrownWeapon->SetOwner(this);
    ThrownWeapon->WeaponMesh = Weapon->WeaponMesh;
    ThrownWeapon->launch();
  }

  // Удаляем предыдущее оружие
  Weapon->Destroy();

  // Меняем на кулаки
  Weapon = Fists;
}

void AHumanoid::useCharacterWeapon(){
  if (Weapon)
    Weapon->startAttacking();
}

// Called every frame
void AHumanoid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
