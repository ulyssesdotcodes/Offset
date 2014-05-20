// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "TopDownPuzzlerBasic.h"
#include "CodePlayerController.h"


ACodePlayerController::ACodePlayerController(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ACodePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Offset", IE_Pressed, this, &ACodePlayerController::HandleOffsetEvent);
}

void ACodePlayerController::ReceiveBeginPlay() {
	const FVector StartTrace = GetCharacter()->GetTransform().GetLocation();
	const FVector EndTrace = StartTrace + FVector(0, 0, -100);

	FCollisionQueryParams TraceParams(FName(TEXT("ZOffsetTrace")), true, this);
	TraceParams.AddIgnoredActor(GetCharacter());

	FHitResult GroundHit;
	GetWorld()->LineTraceSingle(GroundHit, StartTrace, EndTrace, TraceParams, NULL);

	bZOffset = (StartTrace - GroundHit.ImpactPoint).Z;
}

void ACodePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (ShadowCharacter != NULL) 
	{
		ShadowCharacter->GetMovementComponent()->Velocity = GetCharacter()->GetVelocity();

		FVector OffsetLocation = GetCharacter()->GetActorLocation() - OffsetVector;
		ShadowCharacter->SetActorLocationAndRotation(OffsetLocation, GetCharacter()->GetActorRotation(), false);
	}
}

void ACodePlayerController::HandleOffsetEvent() 
{
	if (ShadowCharacter == NULL) 
	{
		PerformOffset();
	}
	else
	{
		ResetOffset();
	}
}

void ACodePlayerController::PerformOffset() {
	ACharacter* const Character = GetCharacter();

	if (Character) 
	{
		FActorSpawnParameters SpawnParams = FActorSpawnParameters();
		SpawnParams.bNoCollisionFail = true;
		SpawnParams.Owner = this;
		FVector CurrentLocation = Character->GetActorLocation();
		FRotator CurrentRotation = Character->GetActorRotation();

		// Spawn the shadow character
		ShadowCharacter = (ATopDownPuzzlerBasicCharacter*)GetWorld()->SpawnActor(ShadowCharacterClass, &CurrentLocation, &CurrentRotation, SpawnParams);

		// Get the input impact point. The impact hit will be 0 for whichever input is not being used.
		FVector InputHit = GetMouseHit() + GetTouchHit();
		InputHit.Z += bZOffset;

		OffsetVector = Character->GetActorLocation() - InputHit;

		Character->SetActorLocation(InputHit);
	}
}

void ACodePlayerController::ResetOffset() {
	ACharacter* const Character = GetCharacter();

	if (Character)
	{
		FActorSpawnParameters SpawnParams = FActorSpawnParameters();
		SpawnParams.bNoCollisionFail = true;
		SpawnParams.Owner = this;
		FVector CurrentLocation = Character->GetActorLocation();
		FRotator CurrentRotation = Character->GetActorRotation();

		// Spawn the shadow character
		ShadowCharacter = (ATopDownPuzzlerBasicCharacter*)GetWorld()->SpawnActor(ShadowCharacterClass, &CurrentLocation, &CurrentRotation, SpawnParams);

		// Get the input impact point. The impact hit will be 0 for whichever input is not being used.
		FVector InputHit = GetMouseHit() + GetTouchHit();
		InputHit.Z += bZOffset;

		OffsetVector = Character->GetActorLocation() - InputHit;

		Character->SetActorLocation(InputHit);
	}
}

FVector ACodePlayerController::GetMouseHit() {
	FHitResult MouseHit;
	GetHitResultUnderCursor(ECC_Visibility, false, MouseHit);

	if (MouseHit.bBlockingHit)
	{
		return MouseHit.ImpactPoint;
	}

	return FVector(0, 0, 0);
}

FVector ACodePlayerController::GetTouchHit() {
	FHitResult TouchHit;
	GetHitResultUnderFinger(ETouchIndex::Touch1, ECC_Visibility, false, TouchHit);

	if (TouchHit.bBlockingHit)
	{
		return TouchHit.ImpactPoint;
	}

	return FVector(0, 0, 0);
}

