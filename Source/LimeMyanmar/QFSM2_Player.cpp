// Fill out your copyright notice in the Description page of Project Settings.


#include "QFSM2_Player.h"

AQFSM2_Player::AQFSM2_Player(){
  // Setting the default imc
  static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCObject(
      TEXT("/Game/Inputs/IMC_Base.IMC_Base"));
  UE_LOG(LogTemp, Warning, TEXT("MAP!"));
  if (IMCObject.Succeeded()) {
    InputMappingContext = IMCObject.Object;
    UE_LOG(LogTemp, Warning, TEXT("YAY!^_^"));
  }

  // Setting up actions
  static ConstructorHelpers::FObjectFinder<UInputAction> MoveActionObj(
      TEXT("/Game/Inputs/Actions/IA_Move.IA_Move"));
  if (MoveActionObj.Succeeded()) {
    MoveAction = MoveActionObj.Object;
  }
}

void AQFSM2_Player::BeginPlay(){
  Super::BeginPlay();
  // Adds IMC_Base
  if (ULocalPlayer *LocalPlayer = GetLocalPlayer()) {
    if (UEnhancedInputLocalPlayerSubsystem *Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
                LocalPlayer)) {
      Subsystem->AddMappingContext(InputMappingContext, 0);
    }
  }
}

void AQFSM2_Player::OnPossess(APawn *InPawn) {
  Super::OnPossess(InPawn);

  if (InPawn) {
    // Get possessed pawn
    PlayerCharacter = Cast<ACoolBob>(InPawn);
  }
}

void AQFSM2_Player::SetupInputComponent(){
  Super::SetupInputComponent();
  if (UEnhancedInputComponent *EnhancedInputComponent =
          Cast<UEnhancedInputComponent>(InputComponent)) {
    if (MoveAction) {
      EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered,
                                         this, &AQFSM2_Player::onMove);
    }
  }
}

void AQFSM2_Player::onMove(const FInputActionValue &Value) {
  if (PlayerCharacter){
    UE_LOG(LogTemp, Warning, TEXT("MOVE!"));
    FVector2D MovementVector = Value.Get<FVector2D>();
    float AxisX = MovementVector.X;
    float AxisY = MovementVector.Y;
    PlayerCharacter->move(AxisX, AxisY);
  }
}