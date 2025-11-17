// Fill out your copyright notice in the Description page of Project Settings.


#include "CoolBob.h"

ACoolBob::ACoolBob() : AHumanoid() { PrimaryActorTick.bCanEverTick = true; }

void ACoolBob::BeginPlay(){
  Super::BeginPlay();
  MoveComp->Deactivate();
  MoveComp->Activate(true);

}

void ACoolBob::PossessedBy(AController *NewController){
  Super::PossessedBy(NewController);
  UE_LOG(LogTemp, Warning, TEXT("MOVEMENT IS ACTIVE %d"),
         GetMovementComponent()->IsActive());
}

// Called every frame
void ACoolBob::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void ACoolBob::move(float x, float y){
  if ((BodyState == EHumanoidBodyStates::dying) ||
      (BodyState == EHumanoidBodyStates::unconscious) ||
      (BodyState == EHumanoidBodyStates::finisher))
    return;
  if (BodyState != EHumanoidBodyStates::moving) {
    BodyState = EHumanoidBodyStates::moving;
  }
  UE_LOG(LogTemp, Warning, TEXT("IMTRYING %f, %f"), x, y);
  AddMovementInput(FVector(x, y, 0.f), 1.f, true);
}