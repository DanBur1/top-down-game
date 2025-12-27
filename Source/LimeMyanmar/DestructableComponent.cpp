// Fill out your copyright notice in the Description page of Project Settings.

#include "DestructableComponent.h"

// Default unreal events
//
// Sets default values for this component's properties
UDestructableComponent::UDestructableComponent() {

}

void UDestructableComponent::BeginPlay(){
  UActorComponent::BeginPlay();

  // Linking the events
  if (GetOwner()) {
    UE_LOG(LogTemp, Warning, TEXT("Health system belongs to %s"),
           *GetOwner()->GetName());
    GetOwner()->OnTakeAnyDamage.AddDynamic(
        this, &UDestructableComponent::onOwnerTookDamage);
  }

}

void UDestructableComponent::onOwnerTookDamage(
    AActor *DamagedActor, float Damage, const class UDamageType *DamageType,
    class AController *InstigatedBy, AActor *DamageCauser) {
  changeHealth(Damage);
}

void UDestructableComponent::TickComponent(
    float DeltaTime, ELevelTick TickType,
    FActorComponentTickFunction *ThisTickFunction) {

}

// Functions

void UDestructableComponent::changeHealth(float damage) {
  health = health - damage;
  if (health < 0) {
    kill();
  }
}


void UDestructableComponent::kill() {
  if (AActor *Owner = GetOwner()) {
    if (has_complex_death)
      OnDeath.Broadcast();
    else {
      UGameplayStatics::SpawnEmitterAtLocation(
          GetWorld(),
          DeathParticleEffect,
          Owner->GetActorLocation(),
          Owner->GetActorRotation()
      );
      Owner->Destroy();
    }
  }
}

void UDestructableComponent::setMaxHealth(float value) { max_health = value; }

void UDestructableComponent::setHealth(float value) { health = value; }

