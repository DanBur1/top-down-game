// Fill out your copyright notice in the Description page of Project Settings.

#include "DestructableComponent.h"

// Default unreal events
//
// Sets default values for this component's properties
UDestructableComponent::UDestructableComponent() {

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
  dead = true;
}

void UDestructableComponent::setMaxHealth(float value) { max_health = value; }

void UDestructableComponent::setHealth(float value) { health = value; }

