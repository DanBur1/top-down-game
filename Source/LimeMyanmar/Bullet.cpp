#include "Bullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ABullet::ABullet() {
  PrimaryActorTick.bCanEverTick = true;
  // Visual
  BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
  RootComponent = BulletMesh;
  // Collision
  BulletMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
  BulletMesh->SetCollisionObjectType(ECC_WorldDynamic);
  BulletMesh->SetCollisionResponseToAllChannels(ECR_Block);
  BulletMesh->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
  BulletMesh->SetNotifyRigidBodyCollision(true);
  BulletMesh->SetEnableGravity(false);
  BulletMesh->SetSimulatePhysics(false);
  BulletMesh->OnComponentHit.AddDynamic(this, &ABullet::onHit);
  // Movement
  ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(
      TEXT("ProjectileMovement"));
  ProjectileMovement->UpdatedComponent = RootComponent;
  ProjectileMovement->InitialSpeed = 2000.f;
  ProjectileMovement->MaxSpeed = 3000.f;
  ProjectileMovement->bRotationFollowsVelocity = true;
  ProjectileMovement->bShouldBounce = false;
  ProjectileMovement->ProjectileGravityScale = 1.f;
}

void ABullet::BeginPlay() {
  Super::BeginPlay();
  if (GetOwner()) {
    UE_LOG(LogTemp, Warning, TEXT("%s launched a bullet"),
           *GetOwner()->GetName());
    BulletMesh->IgnoreActorWhenMoving(GetOwner(), true);
  if ((ProjectileMovement) && (!BarrelDirection.IsZero())) {
      ProjectileMovement->Velocity =
          BarrelDirection * (ProjectileMovement->InitialSpeed+speed_of_gun);
    ProjectileMovement->Activate();
    UE_LOG(LogTemp, Warning,
           TEXT("Spawned bullet at %s, initial speed is %s, direction is %s"),
           *GetActorLocation().ToString(),
           *ProjectileMovement->Velocity.ToString(),
           *BarrelDirection.ToString());
  }
  }
  GetWorldTimerManager().SetTimer(MaxDistanceTimer, this,
                                  &ABullet::selfDestruct, travel_time, false);
}

void ABullet::onHit(UPrimitiveComponent *HitComp, AActor *OtherActor,
                    UPrimitiveComponent *OtherComp, FVector NormalImpulse,
                    const FHitResult &Hit) {
  if (is_explosive)
    applyRadialDamageAtLocation(Hit.ImpactPoint);
  else
    applyDamageToHitActor(OtherActor);
  selfDestruct();
}

void ABullet::applyRadialDamageAtLocation(const FVector &Location) {
  TArray<AActor *> IgnoreActors;
  IgnoreActors.Add(GetOwner());
  UGameplayStatics::ApplyRadialDamage(GetWorld(), damage, Location,
                                      damage_radius, nullptr, IgnoreActors, this,
                                      GetInstigatorController());
}

void ABullet::applyDamageToHitActor(AActor *Actor) {
  UE_LOG(LogTemp, Warning, TEXT("%s is hit"), *Actor->GetName());
  TArray<AActor *> IgnoreActors;
  IgnoreActors.Add(GetOwner());
  UGameplayStatics::ApplyDamage(Actor, damage, GetInstigatorController(),
                                GetOwner(), nullptr);
}

void ABullet::selfDestruct(){
  Destroy();
}

void ABullet::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);
}