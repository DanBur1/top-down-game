// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "DestructableComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LIMEMYANMAR_API UDestructableComponent : public UActorComponent {
  GENERATED_BODY()

public:
  // Variables

  // Flag for whether the character is dead or object is destroyed
  bool dead = false;

  // Functions

  // Constructor
  UDestructableComponent();

protected:
  // Constants

  // Upper border of character's health or object durability
  float max_health = 100;

  // Variables
  // 
  // Character health or object durabiliy
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
  float health = 100;

public:
  // Unreal events

  // Tick event
  virtual void
  TickComponent(float DeltaTime, ELevelTick TickType,
                FActorComponentTickFunction *ThisTickFunction) override;

  // Functions

  // Subtracts damage from health
  void changeHealth(float damage);
  // Processes death of character or destruction of objects
  void kill();
  // Sets maximum value for health
  void setMaxHealth(float value);
  // Sets new value for health
  void setHealth(float value);
};
