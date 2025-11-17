// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMode.h"

AMainMode::AMainMode() {
  // Sets Player as controller
  PlayerControllerClass = AQFSM2_Player::StaticClass();
}

/*void AMainMode::RestartPlayer(AController *NewPlayer) {
  Super::RestartPlayer(NewPlayer);
  if (NewPlayer->GetPawn()) {
    NewPlayer->Possess(NewPlayer->GetPawn());
  } else {
    if (NewPlayer == nullptr) {
      return;
    }
    UE_LOG(LogTemp, Warning, TEXT("START SPAWNING %s"),
           *DefaultPawnClass->GetName());
    FVector SpawnLocation = FVector::ZeroVector;
    FRotator SpawnRotation = FRotator::ZeroRotator;
    APawn *NewPawn = nullptr;

    AActor *PlayerStartActor = FindPlayerStart(NewPlayer);
    if (PlayerStartActor) {
      APlayerStart *PlayerStart = Cast<APlayerStart>(PlayerStartActor);
      if (PlayerStart) {
        SpawnLocation = PlayerStart->GetActorLocation();
        SpawnRotation = PlayerStart->GetActorRotation();
      } else {
        SpawnLocation = PlayerStartActor->GetActorLocation();
        SpawnRotation = PlayerStartActor->GetActorRotation();
      }
    }

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    NewPawn = GetWorld()->SpawnActor<APawn>(DefaultPawnClass, SpawnLocation,
                                            SpawnRotation, SpawnParams);
    if (NewPawn) {
      UE_LOG(LogTemp, Warning, TEXT("POSSES!"));
      NewPlayer->Possess(NewPawn);
    }
  }
}*/

void AMainMode::BeginPlay() { Super::BeginPlay();
  
}