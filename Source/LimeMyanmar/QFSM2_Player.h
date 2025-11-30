// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <EnhancedInputSubsystems.h>
#include <InputMappingContext.h>
#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/PlayerController.h"
#include "CoolBob.h"
#include "QFSM2_Player.generated.h"

/**
 * 
 */
UCLASS()
class LIMEMYANMAR_API AQFSM2_Player : public APlayerController
{
  GENERATED_BODY()
  
  public:
    // Default unreal events
    
    // Constructor
    AQFSM2_Player();
    // Begin play
    virtual void BeginPlay() override;
    // On posses
    virtual void OnPossess(APawn *InPawn) override;
    // Connects actions with functions
    virtual void SetupInputComponent() override;
    // Ticks
    virtual void Tick(float DeltaTime) override;

    // Variables

    // Current mapping context
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputMappingContext *InputMappingContext;
    // Actions
    // IA_Attack
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction *AttackAction;
    // IA_Move
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction *MoveAction;


  private:
    // Variables
    
    ACoolBob *PlayerCharacter;
     
    // Methods

    // Traces a line from mouse to the plane that has "Aim" collision profile. Returns 0 if trace failed
    FVector getAimLocation();
    // Changes controllers rotation according to mouse
    void updateAimRotation(float DeltaTime);
    // Reactions to actions
    // Reaction to IA_Attack
    void onAttack();
    // Reaction to IA_Move
    void onMove(const FInputActionValue &Value);
};
