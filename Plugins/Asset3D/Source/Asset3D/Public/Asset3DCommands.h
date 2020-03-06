// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "Asset3DStyle.h"

class FAsset3DCommands : public TCommands<FAsset3DCommands>
{
public:

	FAsset3DCommands()
		: TCommands<FAsset3DCommands>(TEXT("Asset3D"), NSLOCTEXT("Contexts", "Asset3D", "Asset3D Plugin"), NAME_None, FAsset3DStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};