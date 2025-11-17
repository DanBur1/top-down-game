// Fill out your copyright notice in the Description page of Project Settings.


#include "Humanoid.h"

// Sets default values
AHumanoid::AHumanoid()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
  MoveComp = GetCharacterMovement();
  MoveComp->SetComponentTickEnabled(true);
  MoveComp->SetActive(true);
}

// Called when the game starts or when spawned
void AHumanoid::BeginPlay() {
  UE_LOG(LogTemp, Warning, TEXT("Hello World %s"), *GetMesh()->GetName());
}

// Called every frame
void AHumanoid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
