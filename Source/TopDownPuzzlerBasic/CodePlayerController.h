// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TopDownPuzzlerBasicCharacter.h"
#include "CodePlayerController.generated.h"

/**
 * 
 */
UCLASS(config=Game)
class ACodePlayerController : public APlayerController
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintReadOnly, Category=Offset)
		float bZOffset;

	UPROPERTY(BlueprintReadWrite, Category = Offset, EditAnywhere)
		UClass* ShadowCharacterClass;

	UPROPERTY(BlueprintReadOnly, Category = Offset)
		FVector OffsetVector;

	ATopDownPuzzlerBasicCharacter *ShadowCharacter;

	FVector GetMouseHit();
	FVector GetTouchHit();


protected:
	virtual void SetupInputComponent() OVERRIDE;
	virtual void ReceiveBeginPlay() OVERRIDE;
	virtual void Tick(float) OVERRIDE;

	void HandleOffsetEvent();

	UFUNCTION(BlueprintImplementableEvent)
		virtual void OnPerformOffset();

	void PerformOffset();


	UFUNCTION(BlueprintImplementableEvent)
		virtual void OnResetOffset();
	
	void ResetOffset();
};
