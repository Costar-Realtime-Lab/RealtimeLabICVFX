#include "RealtimeLabICVFXSettings.h"

URealtimeLabICVFXSettings::URealtimeLabICVFXSettings()
{
	FParse::Value(FCommandLine::Get(), TEXT("-StageFriendlyName="), CommandLineFriendlyName);
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
