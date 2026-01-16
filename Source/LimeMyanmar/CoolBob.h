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

    // Properties

    // В .h файле класса (GameMode, Actor, Component)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
    class UDataTable *ScoreTable;

    // Methods
  
    // Sets score of player based on the name of action he did
    UFUNCTION(BlueprintCallable, Category = "Data")
    void changeScore(FName RowName);
    // Moves player around
    void move(float x, float y);

  protected:
    // Properties

    // Player score
    UPROPERTY(EditAnywhere, Category = "Others")
    int score = 0;
};
