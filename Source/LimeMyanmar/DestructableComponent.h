// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Delegates/Delegate.h"
#include "DestructableComponent.generated.h"

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
  void onOwnerTookDamage(AActor *DamagedActor, float Damage,
                         const class UDamageType *DamageType,
                         class AController *InstigatedBy, AActor *DamageCauser);
  // Tick event
  virtual void
  TickComponent(float DeltaTime, ELevelTick TickType,
                FActorComponentTickFunction *ThisTickFunction) override;


  // Variables

  // Flag for whether the character is dead or object is destroyed
  bool dead = false;

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
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
  float health = 100;

};
