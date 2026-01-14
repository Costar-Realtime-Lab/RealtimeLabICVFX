![CoSTAR Realtime lab logo and banner](Resources/RealtimeLab.png)
# RealtimeLabICVFX
ICVFX configuration plugin for the CoSTAR Realtime Lab.

## Dependencies
Engine plugins:
- LiveLink
- LiveLinkHub
- nDisplay
- [Optional] Stage Monitor

Third-party plugins:
- MoSysVPFree ([Download on Fab](https://www.fab.com/listings/4b0ddb44-8d3d-4eb4-8009-9da580f54b38))
- CanonLiveLinkPlugin ([Download from Canon](https://www.canon-europe.com/support/consumer/products/camcorders/cinema-eos/eos-c400.html?type=download&detailId=tcm:13-2389615&os=windows%2011&language=en&productTcmUri=tcm:13-2387148))
- [Optional] NVIDIA DLSS ([Download from NVIDIA](https://developer.nvidia.com/rtx/dlss?sortBy=developer_learning_library%2Fsort%2Ffeatured%3Adesc%2Ctitle%3Aasc#section-getting-started))
## Quick Start
> [!IMPORTANT]
> For Switchboard to launch correctly, your project must be on DEATH's `D:` drive!
### 1. Remove Sublevels
For nDisplay stability, all actors should be moved from sublevels into the persistent level. 
This can be done as follows:
1. **Make a backup of the original level as these steps cannot be undone.**
2. Open Levels window
3. Right click on the first sublevel below the persistent level.
4. Click 'Select Actors'
5. Right click on the persistent level.
6. Click 'Move Selected Actors to Level'
7. Delete the sublevel by selecting it and pressing the Delete key.
8. Repeat steps 3-7 until all sublevels have been removed.
### 2. Set up nDisplay
- Drag nDisplaySublevel into the desired level
- Break sublevel
- Set CineCamera association
- Position nDisplay configration in world
### 3. Set up LiveLinkHub
`TODO: Setting up live link config / package live link config with plugin`

`TODO: This may be automated by the SwitchboardConfigGenerator`
### 4. Set up FreeFileSync
`TODO: This will be automated in future by the SwitchboardConfigGenerator`
- Create new configuration
- Add an entry to copy from DEATH to each of WAR, FAMINE, and PESTILENCE. 

> [!IMPORTANT]
> The relative path from the drive root on each machine should be the same. For example:
>
> `D:/folder/my_project` -> `W:/folder/my_project`
>
> and likewise for FAMINE (`X:`) and PESTILENCE (`Y:`).
- Set Synchronization mode to **mirror**.
- It is recommended to filter out temporary and non-required files to reduce synchronization time. Add the following to the exclude list:
    - `.vs/`
    - `*/Intermediate/`
    - `Saved/`
    - `*.pdb`
- Compare and Synchronize to sync files across all machines.
### 5. Setting up Switchboard with SwitchboardConfigGenerator
- Run `SwitchboardConfigGenerator.exe`. It is located in the root directory of the **RealtimeLabICVFX** plugin.
- Input the path to the engine directory when prompted. By default, Unreal Engine is installed to `C:/Program Files/Epic Games/UE_5.x/Engine` but the actual location will depend on your engine version and install location.
- `SwitchboardConfigGenerator` should have created `<project name>_SwitchboardConfig.json` next to your `.uproject` file.
- Launch Switchboard.
- Go to `Configs > Load Config > Browse...` and browse to `<project name>_SwitchboardConfig.json`. Open the generated config.
- Select the level containing your nDisplay config from the `Level:` dropdown. You may need to click the refresh button to the right of the dropdown if your level is not shown in the dropdown.
### 6. Customizing Switchboard Config via `StudioProperties.json`
`SwitchboardConfigGenerator` will create a `StudioProperties.json` within the plugin root directory. This can be modified to customize the Switchboard configuration that is generated (e.g. to customize CVars for specific render nodes).

For more information on configuration options see the [Studio Properties Reference](Docs/StudioPropertiesReference.md).

After modifying `StudioProperties.json`, run `SwitchboardConfigGenerator.exe` again to update the configuration. This will overwrite any additional configuration you have done within Switchboard, so ideally all additional config should be performed within `StudioProperties.json`.
### 7. Launching with Switchboard
Pre-launch checklist:
- All render nodes and LED processors are switched on and genlocked / framelocked. See [Framelock Verifcation Guide](Docs/FramelockVerification.md).
- No instances of Unreal are currently running.
- Switchboard Listener is running on all control and render nodes.

Launch Sequence:
- Launch Switchboard with the configuration for your project.
- Use FreeFileSync to synchronize the project between the control machine and all render nodes.
- Click plus button in right hand side of multi-user session dialog to increment session ID. **You MUST do this between every launch.**
- Connect to all Switchboard Listener instances for each device in Switchboard.
- Launch all nDisplay and editor devices in Switchboard.

## Troubleshooting
- It is sometimes recommended to run Switchboard Listener as Administrator on all render nodes.
- Remember to increment the multi-user session ID between launches.
- Delete `StudioProperties.json` and `<project name>_SwitchboardConfig.json` and regenerate via `SwitchboardConfigGenerator.exe` to restore Switchboard config to default.

## TODO
- LED wall meshes: Consistent naming between static mesh assets, static mesh components in the nDisplay config, and viewports in the nDisplay cluster. (E.g., wild wall meshes are labelled left vs right, static mesh components are enumerated - which associates with which?).
