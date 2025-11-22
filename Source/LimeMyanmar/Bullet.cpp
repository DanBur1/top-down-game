#include "Bullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ABullet::ABullet() {
  PrimaryActorTick.bCanEverTick = true;
  // Visual
  BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
  // Collision
  BulletMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
  BulletMesh->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
  BulletMesh->SetNotifyRigidBodyCollision(true);
  BulletMesh->OnComponentHit.AddDynamic(this, &ABullet::onHit);
  // Movement
  ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(
      TEXT("ProjectileMovement"));
  ProjectileMovement->UpdatedComponent = BulletMesh;
  ProjectileMovement->InitialSpeed = 2000.f;
  ProjectileMovement->MaxSpeed = 5000.f;
  ProjectileMovement->bRotationFollowsVelocity = true;
  ProjectileMovement->bShouldBounce = true;
  ProjectileMovement->ProjectileGravityScale = 1.f;
}

void ABullet::BeginPlay() {
  Super::BeginPlay();
  if (GetOwner()) {
    BulletMesh->IgnoreActorWhenMoving(GetOwner(), true);
  }
  if ((ProjectileMovement) && (!BarrelDirection.IsZero())) {
    ProjectileMovement->Velocity =
        BarrelDirection * (ProjectileMovement->InitialSpeed + speed_of_gun);
    UE_LOG(LogTemp, Warning,
           TEXT("Spawned bullet at %s, initial speed is %s, "),
           *GetActorLocation().ToString(),
           *ProjectileMovement->Velocity.ToString());

    ProjectileMovement->SetActive(true);
  }
}

void ABullet::onHit(UPrimitiveComponent *HitComp, AActor *OtherActor,
                    UPrimitiveComponent *OtherComp, FVector NormalImpulse,
                    const FHitResult &Hit) {
  if (is_explosive)
    applyRadialDamageAtLocation(Hit.ImpactPoint);
  else
    applyDamageToHitActor(OtherActor);
  Destroy();
}

void ABullet::applyRadialDamageAtLocation(const FVector &Location) {
  TArray<AActor *> IgnoreActors;
  IgnoreActors.Add(GetOwner());
  UGameplayStatics::ApplyRadialDamage(GetWorld(), damage, Location,
                                      damage_radius, nullptr, IgnoreActors, this,
                                      GetInstigatorController());
}

void ABullet::applyDamageToHitActor(AActor *Actor) {
  TArray<AActor *> IgnoreActors;
  IgnoreActors.Add(GetOwner());
  UGameplayStatics::ApplyDamage(Actor, damage, GetInstigatorController(),
                                GetOwner(), nullptr);
}

void ABullet::Tick(float DeltaTime) { Super::Tick(DeltaTime); }