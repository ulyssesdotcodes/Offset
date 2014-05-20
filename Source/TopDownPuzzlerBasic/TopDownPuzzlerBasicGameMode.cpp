// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "TopDownPuzzlerBasic.h"
#include "TopDownPuzzlerBasicGameMode.h"
#include "CodePlayerController.h"

ATopDownPuzzlerBasicGameMode::ATopDownPuzzlerBasicGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	PlayerControllerClass = ACodePlayerController::StaticClass();
}


