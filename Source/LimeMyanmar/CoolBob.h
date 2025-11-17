// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Humanoid.h"
#include "CoolBob.generated.h"

/**
 * 
 */
UCLASS()
class LIMEMYANMAR_API ACoolBob : public AHumanoid
{
	GENERATED_BODY()

  public:
    // Default unreal events

    // Constructor
    ACoolBob();
    virtual void BeginPlay() override;
    // Triggered when possessed by NewController
    virtual void PossessedBy(AController *NewController) override;
    virtual void Tick(float DeltaTime) override;

    // Methods
  
    // Moves player around
    void move(float x, float y);
};
