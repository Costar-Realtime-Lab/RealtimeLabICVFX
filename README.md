![CoSTAR Realtime lab logo and banner](Resources/RealtimeLab.png)
# RealtimeLabICVFX
ICVFX configuration plugin for the CoSTAR Realtime Lab.

## Dependencies
Engine plugins:
- LiveLink
- LiveLinkHub
- nDisplay

Third-party plugins:
- MoSysVPFree ([Download on Fab](https://www.fab.com/listings/4b0ddb44-8d3d-4eb4-8009-9da580f54b38))
- CanonLiveLinkPlugin ([Download from Canon](https://www.canon-europe.com/support/consumer/products/camcorders/cinema-eos/eos-c400.html?type=download&detailId=tcm:13-2389615&os=windows%2011&language=en&productTcmUri=tcm:13-2387148))
- [Optional] NVIDIA DLSS ([Download from NVIDIA](https://developer.nvidia.com/rtx/dlss?sortBy=developer_learning_library%2Fsort%2Ffeatured%3Adesc%2Ctitle%3Aasc#section-getting-started))
## Quick Start
> [!IMPORTANT]
> For Switchboard to launch correctly, your project must be on DEATH's `D:` drive!
### Setting up nDisplay configuration
- Drag nDisplaySublevel into the desired level
- Break sublevel
- Set CineCamera association
- Position nDisplay configration in world
### Setting up LiveLinkHub
`TODO: Setting up live link config / package live link config with plugin`
### Setting up FreeFileSync
- Create new configuration
- Add an entry to copy from DEATH to each of WAR, FAMINE, and PESTILENCE. The relative path from the drive root on each machine should be the same.
- Set Synchronization mode to **mirror**.
- Compare and Synchronize to sync files across all machines.

`TODO: Setting up ignore paths.`
### Setting up Switchboard
- Launch Switchboard
- Create a new Switchboard Config, saving the config in the same folder as the uproject.
- Select the level that you added the nDisplay config to from the dropdown.
- Add nDisplay device from the Add Device dropdown. Select 'Populate' to automatically detect the nDisplay config asset. Launch as 'Standalone (ICVFX)'
- Add Unreal device from the Add Device dropdown. For name, put "Editor" and for IP address put the IP Address of DEATH: `192.168.56.20`.
- Add LiveLinkHub device from the Add Device dropdown. For name, put "LLHub" and for IP address put the IP Address of DEATH `192.168.56.20`.
### Launching with Switchboard
Pre-launch checklist:
- All render nodes and LED processors are switched on and genlocked / framelocked. `TODO: See framelock verification`
- No instances of Unreal are currently running.
- Switchboard Listener is running on all control and render nodes: DEATH, WAR, FAMINE, and PESTILENCE.

Launch Sequence:
- Launch Switchboard with the configuration for your project.
- Click plus button in right hand side of multi-user session dialog to increment session ID. **You MUST do this between every launch.**
- Connect to all Switchboard Listener instances for each device in Switchboard.
- Launch all devices in Switchboard.

## Troubleshooting
- It is sometimes recommended to run Switchboard Listener as Administrator on all render nodes.

## TODO

- LED wall meshes: Consistent naming between static mesh assets, static mesh components in the nDisplay config, and viewports in the nDisplay cluster. (E.g., wild wall meshes are labelled left vs right, static mesh components are enumerated - which associates with which?).
