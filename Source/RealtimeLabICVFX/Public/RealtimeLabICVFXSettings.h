#pragma once

#include "Engine/DeveloperSettings.h"

#include "RealtimeLabICVFXSettings.generated.h"


UCLASS(config=Game)
class REALTIMELABICVFX_API URealtimeLabICVFXSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	URealtimeLabICVFXSettings();

	//~ Begin UDeveloperSettingsInterface
	virtual FName GetCategoryName() const override;
#if WITH_EDITOR
	virtual FText GetSectionText() const override;
#endif
	//~ End UDeveloperSettingsInterface

public:
	/**
	 * A friendly name for this instance of Unreal that is given through the command line.
	 */
	FName CommandLineFriendlyName;

};
