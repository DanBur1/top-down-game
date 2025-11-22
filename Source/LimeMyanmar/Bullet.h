#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystem.h"
#include "Bullet.generated.h"

UCLASS()
class LIMEMYANMAR_API ABullet : public AActor {
  GENERATED_BODY()

public:
  // Default unreal events

  // Constructor
  ABullet();

  // Properties

  // Damage dealt by bullet
  UPROPERTY(EditDefaultsOnly, Category = "Damage")
  float damage = 20.f;

protected:
  // Default unreal events

  // Plays when actor is placed in the world or the game is started
  virtual void BeginPlay() override;

  // Properties

  // Model
  UPROPERTY(VisibleAnywhere, Category = "Components")
  UStaticMeshComponent *BulletMesh;
  // Determines which function is used to deal damage
  bool is_explosive = false;
  // Projectile movement component
  UPROPERTY(VisibleAnywhere, Category = "Components")
  class UProjectileMovementComponent *ProjectileMovement;
  // Radius of splash damage
  UPROPERTY(EditDefaultsOnly, Category = "Damage")
  float damage_radius = 50.f;

  // Methods
  
  // Damage function used when the projectile is explosive
  void applyRadialDamageAtLocation(const FVector &Location);
  // Reaction to solid collision
  UFUNCTION()
  void onHit(UPrimitiveComponent *HitComp, AActor *OtherActor,
             UPrimitiveComponent *OtherComp, FVector NormalImpulse,
             const FHitResult &Hit);
  // Damage function used when the projectile is not explosive
  void applyDamageToHitActor(AActor *Actor);

public:
  // Variables

  // Vector of owner
  FVector BarrelDirection;
  // Speed with which owner moves
  float speed_of_gun;

  // Functions

  // Tick tock on the clock
  virtual void Tick(float DeltaTime) override;
};