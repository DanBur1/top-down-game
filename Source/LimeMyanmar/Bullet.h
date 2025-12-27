#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystem.h"
	#include "EngineUtils.h"
#include "Bullet.generated.h"

UCLASS()
class LIMEMYANMAR_API ABullet : public AActor {
  GENERATED_BODY()

private:

  // Properties
  
  // Time to self destruct
  UPROPERTY()
  FTimerHandle MaxDistanceTimer;

public:
  // Default unreal events

  // Constructor
  ABullet();

  // Properties

    // Model
  UPROPERTY(VisibleAnywhere, Category = "Components")
  UStaticMeshComponent *BulletMesh;
  // Damage dealt by bullet
  UPROPERTY(EditDefaultsOnly, Category = "Bullet properties")
  float damage = 20.f;
  // Time the bullet can fly before being deleted
  UPROPERTY(EditDefaultsOnly, Category = "Bullet properties")
  float travel_time = 0.f;

protected:
  // Default unreal events

  // Plays when actor is placed in the world or the game is started
  virtual void BeginPlay() override;

  // Properties

  // Radius of splash damage
  UPROPERTY(EditDefaultsOnly, Category = "Bullet properties")
  float damage_radius = 50.f;
  // Determines which function is used to deal damage
  UPROPERTY(VisibleAnywhere, Category = "Others")
  bool is_explosive = false;
  // Projectile movement component
  UPROPERTY(VisibleAnywhere, Category = "Components")
  class UProjectileMovementComponent *ProjectileMovement;

  // Methods
  
  // Damage function used when the projectile is explosive
  void applyRadialDamageAtLocation(const FVector &Location);
  // Reaction to solid collision
  UFUNCTION(BlueprintCallable, Category = "Weapon")
  void onHit(UPrimitiveComponent *HitComp, AActor *OtherActor,
             UPrimitiveComponent *OtherComp, FVector NormalImpulse,
             const FHitResult &Hit);
  // Damage function used when the projectile is not explosive
  void applyDamageToHitActor(AActor *Actor);
  // Deletes the bullet
  void selfDestruct();

public:
  // Variables

  // Vector of owner
  UPROPERTY()
  FVector BarrelDirection;
  // Speed with which owner moves
  UPROPERTY()
  float speed_of_gun;

  // Functions

  // Tick tock on the clock
  UFUNCTION()
  virtual void Tick(float DeltaTime) override;
};