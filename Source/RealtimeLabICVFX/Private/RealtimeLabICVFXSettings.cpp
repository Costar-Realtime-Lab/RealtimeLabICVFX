#include "RealtimeLabICVFXSettings.h"
#include "Misc/CommandLine.h"


URealtimeLabICVFXSettings::URealtimeLabICVFXSettings()
{
	FParse::Value(FCommandLine::Get(), TEXT("-StageFriendlyName="), CommandLineFriendlyName);
	FParse::Value(FCommandLine::Get(), TEXT("-TopologyFriendlyName="), CommandLineTopologyFriendlyName);
}

FName URealtimeLabICVFXSettings::GetCategoryName() const
{
	return TEXT("Plugins");
}

#if WITH_EDITOR
FText URealtimeLabICVFXSettings::GetSectionText() const
{
	return NSLOCTEXT("RealtimeLabICVFXPlugin", "RealtimeLabICVFXSettingsSection", "RealtimeLabICVFX");
}
#endif
