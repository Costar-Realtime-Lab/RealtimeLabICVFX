#include "RealtimeLabICVFXSettings.h"

#include "Engine/Engine.h"
#include "HAL/FileManager.h"
#include "HAL/IConsoleManager.h"
#include "Misc/App.h"
#include "Misc/Paths.h"


TOptional<FString> TryParsePath(FString Path)
{
	// We are expecting an absolute path with no filename specified

	if (FPaths::IsRelative(Path))
		return NullOpt;

	if (!FPaths::GetExtension(Path).IsEmpty())
		return NullOpt;

	if (!Path.EndsWith(TEXT("/")))
		Path.Append(TEXT("/"));

	if (!FPaths::GetCleanFilename(Path).IsEmpty())
		return NullOpt;

	// Finally make sure the path is platform friendly
	IFileManager& FileManager = IFileManager::Get();
	FString NativePath = FileManager.ConvertToAbsolutePathForExternalAppForWrite(*Path);

	// Ensure we can write the trace file appropriately
	const FString WriteDir = FPaths::GetPath(NativePath);
	if (!FPaths::IsDrive(WriteDir))
	{
		if (!FileManager.MakeDirectory(*WriteDir, true))
		{
			return NullOpt;
		}
	}

	return Path;
}

static void RequestBeginTracing(const TArray<FString>& Args)
{
	TOptional<FString> Path;
	if (!Args.IsEmpty())
	{
		 Path = TryParsePath(Args[0]);

		if (!Path)
		{
			UE_LOG(LogConsoleResponse, Warning, TEXT("Ignoring Path argument: Path should be a writable directory (not a file)!"));
		}
	}

	// Get a name for the trace file
	const URealtimeLabICVFXSettings* Settings = GetMutableDefault<URealtimeLabICVFXSettings>();
	FString FriendlyDeviceName = Settings->CommandLineFriendlyName;
	FString FriendlyTopologyName = Settings->CommandLineTopologyFriendlyName;

	FStringFormatNamedArguments FormatArgs;
	FormatArgs.Add(TEXT("ProjectName"), FApp::GetProjectName());
	FormatArgs.Add(TEXT("StageName"), FriendlyDeviceName);
	FormatArgs.Add(TEXT("TopologyName"), FriendlyTopologyName.Len() ? FriendlyTopologyName + TEXT("_") : FString{});
	FormatArgs.Add(TEXT("Time"), FDateTime::Now().ToString(TEXT("%Y%m%d_%H%M%S")));
	FString Filename = FString::Format(TEXT("{ProjectName}_{TopologyName}{StageName}_{Time}.utrace"), FormatArgs);

	FString FullPath = FPaths::Combine(Path.Get(""), Filename);
	FString Exec = FString::Format(TEXT("Trace.File {0}"), { FullPath });

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
	TEXT("[Path] - Begins tracing to a local file with an informative name."
		"Path can optionally specify the directory to save the file. If omitted will be written to default profiling directory."
		"Must be a directory name. For use in clustered rendering to identify which trace originated from which node."
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
