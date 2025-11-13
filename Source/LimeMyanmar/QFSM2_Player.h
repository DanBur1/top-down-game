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

    // Variables

    // Current mapping context
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputMappingContext *InputMappingContext;
    // Actions
    // IA_Move
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction *MoveAction;


  private:
    // Variables
    
    ACoolBob *PlayerCharacter;
     
    // Methods
    
    // Setting up the controls
    // Reaction to IA_Move
    void onMove(const FInputActionValue &Value);
};
