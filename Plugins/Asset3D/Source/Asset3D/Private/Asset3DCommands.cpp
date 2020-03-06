// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Asset3DCommands.h"

#define LOCTEXT_NAMESPACE "FAsset3DModule"

void FAsset3DCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "Asset3D", "Bring up Asset3D window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
