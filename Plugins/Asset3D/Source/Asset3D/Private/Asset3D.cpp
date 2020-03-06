// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Asset3D.h"
#include "Asset3DStyle.h"
#include "Asset3DCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "HAL/FileManagerGeneric.h"


#include "Framework/MultiBox/MultiBoxBuilder.h"

static const FName Asset3DTabName("Asset3D");

#define LOCTEXT_NAMESPACE "FAsset3DModule"

void FAsset3DModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FAsset3DStyle::Initialize();
	FAsset3DStyle::ReloadTextures();

	FAsset3DCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FAsset3DCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FAsset3DModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FAsset3DModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FAsset3DModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(Asset3DTabName, FOnSpawnTab::CreateRaw(this, &FAsset3DModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FAsset3DTabTitle", "Asset3D"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FAsset3DModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FAsset3DStyle::Shutdown();

	FAsset3DCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(Asset3DTabName);
}

TSharedRef<SDockTab> FAsset3DModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FString ThePath = FPaths::GetPath("D:\\practice of unreal book\\Inventory_Pickup\\Content\\Assets\\Meshes\\"); // Specify the path
	
	TArray<FString> Assets;
	Assets.Empty();

	FString Path = ThePath + "\\*.Uasset";
	FString allAsset;
	FFileManagerGeneric::Get().FindFiles(Assets, *Path, true, false);

	for (int i = 0; i < Assets.Num(); i++)
	{
		allAsset = allAsset + " " + Assets[i] + "\n";
	}

	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "{0}"),
		FText::FromString(allAsset)			//All Assets String
	);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Top)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FAsset3DModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(Asset3DTabName);
}

void FAsset3DModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FAsset3DCommands::Get().OpenPluginWindow);
}

void FAsset3DModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FAsset3DCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAsset3DModule, Asset3D)