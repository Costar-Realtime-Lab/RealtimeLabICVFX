#include "RealtimeLabICVFXSettings.h"


static void RequestBeginTracing(const TArray<FString>& Args)
{	
	// Get a name for the trace file
	FName FriendlyDeviceName = GetMutableDefault<URealtimeLabICVFXSettings>()->CommandLineFriendlyName;
;	FString Filename = FString::Format(TEXT("%Y%m%d_%H%M%S_{0}.utrace"), { FriendlyDeviceName.ToString() });
	Filename = FDateTime::Now().ToString(*Filename);

	FString Exec = FString::Format(TEXT("Trace.File {0}"), { Filename });

	// Execute console command to start tracing to file
	GEngine->Exec(nullptr, *Exec);
}

static void RequestStopTracing(const TArray<FString>& Args)
{
	// Execute console command to stop tracing
	GEngine->Exec(nullptr, TEXT("Trace.Stop"));
}


////////////////////////////////////////////////////////////////////////////////


static FAutoConsoleCommand TraceClusterBeginCmd(
	TEXT("TraceCluster.Start"),
	TEXT("Begins tracing to a local file named by the stage name of the Unreal Instance."
		"For use in clustered rendering to identify which trace originated from which node."
	),
	FConsoleCommandWithArgsDelegate::CreateStatic(RequestBeginTracing)
);

static FAutoConsoleCommand TraceClusterEndCmd(
	TEXT("TraceCluster.Stop"),
	TEXT("Ends cluster tracing to a local file named by the stage name of the Unreal Instance."
		"For use in clustered rendering to identify which trace originated from which node."
	),
	FConsoleCommandWithArgsDelegate::CreateStatic(RequestStopTracing)
);
