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
  // Getting the shooter of the bullet
  if (GetOwner()) {
    UE_LOG(LogTemp, Warning, TEXT("%s launched a bullet"),
           *GetOwner()->GetName());
    
    // Getting shooters other bullets to make sure they don't collide.
    // While it does take more time then just making bullet collision
    // non-blocking with other bullets it allows to shoot down bullets
    // fired by others which i believe is pretty sick
    for (TActorIterator<ABullet> It(GetWorld()); It; ++It) {
      ABullet *OtherBullet = *It;
      if (OtherBullet != this && OtherBullet->GetOwner() == GetOwner()) {
        BulletMesh->IgnoreActorWhenMoving(OtherBullet, true);
        UE_LOG(LogTemp, Log, TEXT("Bullet ignores sibling bullet: %s"),
               *OtherBullet->GetName());
      }
    }

    // Ignoring the owner to make sure you can't accidentally kill self
    BulletMesh->IgnoreActorWhenMoving(GetOwner(), true);
    
    // Setting up the projectile movement
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

  // Setting the projectile to selfdistruct if it can't reach anything for too long
  GetWorldTimerManager().SetTimer(MaxDistanceTimer, this,
                                  &ABullet::selfDestruct, travel_time, false);

  // Physics
  BulletMesh->SetNotifyRigidBodyCollision(true);
  BulletMesh->SetEnableGravity(false);
  BulletMesh->SetSimulatePhysics(false);
  BulletMesh->OnComponentHit.AddDynamic(this, &ABullet::onHit);
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
  // Not sure if i should keep it since any other game that has explosives
  // allows players to die from splash damage
  TArray<AActor *> IgnoreActors;
  IgnoreActors.Add(GetOwner());

  // Even though this game won't have exploding bullets, might be useful in the future
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