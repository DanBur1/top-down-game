// Fill out your copyright notice in the Description page of Project Settings.


#include "QFSM2_Player.h"

AQFSM2_Player::AQFSM2_Player(){
  // All action initializiation moved to blueprint
}

void AQFSM2_Player::BeginPlay(){
  Super::BeginPlay();
}

void AQFSM2_Player::OnPossess(APawn *InPawn) {
  Super::OnPossess(InPawn);

  if (InPawn) {
    UE_LOG(LogTemp, Warning, TEXT("CONTROLLER FOUND A PAWN"));
    // Get possessed pawn
    PlayerCharacter = Cast<ACoolBob>(InPawn);
    // Adds IMC_Base
    if (ULocalPlayer *LocalPlayer = GetLocalPlayer()) {
      if (UEnhancedInputLocalPlayerSubsystem *Subsystem =
              ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
                  LocalPlayer)) {
        Subsystem->AddMappingContext(InputMappingContext, 0);
      }
    }
  }
}

void AQFSM2_Player::SetupInputComponent(){
  Super::SetupInputComponent();
  UE_LOG(LogTemp, Warning, TEXT("Setting controls"));
  // Make mouse visible
  SetShowMouseCursor(true);

  // Bind functions to actions
  if (UEnhancedInputComponent *EnhancedInputComponent =
          Cast<UEnhancedInputComponent>(InputComponent)) {
    // Attacking
    if (AttackAction) {
      EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started,
                                         this, &AQFSM2_Player::onAttackStart);
    }
    if (AttackAction) {
      EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Completed,
                                         this, &AQFSM2_Player::onAttackEnd);
    }
    // Movement
    if (MoveAction) {
      EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered,
                                         this, &AQFSM2_Player::onMove);
    }
    // Picking/Throwing weapon
    if (ReplaceWeaponAction) {
      EnhancedInputComponent->BindAction(ReplaceWeaponAction, ETriggerEvent::Started,
                                         this, &AQFSM2_Player::onReplaceWeapon);
    }
  }
}

void AQFSM2_Player::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);
  updateAimRotation(DeltaTime);
}

FVector AQFSM2_Player::getAimLocation(){

  // If not possesed return 0
  if (!PlayerCharacter)
    return FVector::ZeroVector;

  // Getting mouse coordinates
  FVector2D MousePosition;
  GetMousePosition(MousePosition.X, MousePosition.Y);
  FVector WorldLocation, WorldDirection;
  DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

  // Normalizing mouse coordinates with aiming field using trace collision
  FHitResult HitResult;
  FCollisionQueryParams QueryParams;
  bool has_hit = GetWorld()->LineTraceSingleByChannel(
      HitResult, WorldLocation, WorldLocation + WorldDirection * 10000,
      ECC_GameTraceChannel1, 
      QueryParams);
  if (has_hit) {
    return HitResult.Location;
  }

  // If aiming field isn't there
  return FVector::ZeroVector;
}

void AQFSM2_Player::updateAimRotation(float DeltaTime) {
  // Ignore if mouse location is 0 (cause it usually means getAimLocation failed)
  FVector AimLocation = getAimLocation();
  if (AimLocation.IsZero())
    return;

  // Ignore if not posessed
  if (PlayerCharacter) {
    
    // Get rotation z value from two points the character and the mouse 
    FVector AimDirection =
        (AimLocation - PlayerCharacter->GetActorLocation()).GetSafeNormal();
    FRotator NewRotation = AimDirection.Rotation();
    NewRotation.Pitch =
        0.0f;

    // Smooth controller rotation
    FRotator CurrentRotation = GetControlRotation();
    FRotator TargetRotation =
        FMath::RInterpTo(CurrentRotation, NewRotation, DeltaTime, 10.0f);
    SetControlRotation(TargetRotation);
  }
}

void AQFSM2_Player::onAttackStart(){
  if (PlayerCharacter){
    PlayerCharacter->useCharacterWeapon();
  }
}

void AQFSM2_Player::onAttackEnd() {
  if (PlayerCharacter) {
    PlayerCharacter->stopUsingWeapon();
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

void AQFSM2_Player::onReplaceWeapon(){
  if (PlayerCharacter){
    UE_LOG(LogTemp, Warning, TEXT("PICK!"));
    PlayerCharacter->replaceWeapon();
  }
}