// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "CoolBob.h"
#include "QFSM2_Player.h"
#include "GameFramework/GameMode.h"
#include "MainMode.generated.h"

/**
 * 
 */
UCLASS()
class LIMEMYANMAR_API AMainMode : public AGameMode
{
	GENERATED_BODY()
  public:
    // Unreal default events

    // Constructor
    AMainMode();
    // BeginPlay
    virtual void BeginPlay() override;
};
