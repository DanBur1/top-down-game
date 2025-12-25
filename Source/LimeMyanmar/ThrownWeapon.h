// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ThrownWeapon.generated.h"

UCLASS()
class LIMEMYANMAR_API AThrownWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Default Unreal events
	
	// Sets default values for this actor's properties
	AThrownWeapon();
  // Called every frame
  virtual void Tick(float DeltaTime) override;

	// Properties

	// Mesh
  UPROPERTY(VisibleAnywhere, Category = "Components")
  UStaticMeshComponent *WeaponMesh;

	// Methods

	// Sets up the projectile to be launched
  void launch();

protected:
	// Default Unreal events

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Properties

	// Movement component of the projectile
  UPROPERTY(VisibleAnywhere, Category = "Components")
  UProjectileMovementComponent *ProjMovement;

	// Methods

};
