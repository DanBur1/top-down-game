// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Delegates/Delegate.h"
#include "DestructableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LIMEMYANMAR_API UDestructableComponent : public UActorComponent {
  GENERATED_BODY()

public:
  // Unreal events

  // Constructor
  UDestructableComponent();
  // Begin play
  virtual void BeginPlay() override;
  // OnTakeDamage
  UFUNCTION()
  void onOwnerTookDamage(AActor *DamagedActor, float Damage,
                         const class UDamageType *DamageType,
                         class AController *InstigatedBy, AActor *DamageCauser);
  // Tick event
  virtual void
  TickComponent(float DeltaTime, ELevelTick TickType,
                FActorComponentTickFunction *ThisTickFunction) override;


  // Properties

  // A particle effect that plays if an actor has no death event reaction and gets destroyed
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
  class UParticleSystem *DeathParticleEffect;
  // Flag that is set false for actors that can't process death/destruction so
  // they get destroyed here instead of calling an event
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
  bool has_complex_death = false;
  // Flag for components of dead actors
  UPROPERTY(BlueprintReadOnly, Category = "Health")
  bool is_dead = false;

  // Events

  // Character is dead
  UPROPERTY(BlueprintAssignable, Category = "Health")
  FOnDeathSignature OnDeath;

  // Functions

  // Subtracts damage from health
  void changeHealth(float damage);
  // Processes death of character or destruction of objects
  void kill();
  // Sets maximum value for health
  void setMaxHealth(float value);
  // Sets new value for health
  void setHealth(float value);

protected:
  // Constants

  // Upper border of character's health or object durability
  float max_health = 100;

  // Properties
  // 
  // Character health or object durabiliy
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
  float health = 100;

};
