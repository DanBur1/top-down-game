#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystem.h"
#include "Bullet.generated.h"

UCLASS()
class LIMEMYANMAR_API ABullet : public AActor {
  GENERATED_BODY()

public:
  ABullet();

protected:
  // Variables and components

  UPROPERTY(VisibleAnywhere, Category = "Components")
  UStaticMeshComponent *BulletMesh;
  // Projectile movement component
  UPROPERTY(VisibleAnywhere, Category = "Components")
  class UProjectileMovementComponent *ProjectileMovement;
  // Radius of splash damage
  UPROPERTY(EditDefaultsOnly, Category = "Damage")
  float DamageRadius = 50.f;
  // Damage in the location of the hit
  UPROPERTY(EditDefaultsOnly, Category = "Damage")
  float DamageAmount = 20.f;

  // Functions

  virtual void BeginPlay() override;

  UFUNCTION()
  void OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor,
             UPrimitiveComponent *OtherComp, FVector NormalImpulse,
             const FHitResult &Hit);

  void ApplyRadialDamageAtLocation(const FVector &Location);

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