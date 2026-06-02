# Studio Properties Reference
> [!WARNING]
> Studio Properties are subject to change and documentation may not be up to date at all times.
## IP Addresses
Each machine in the studio setup can be included in the addresses structure. Each IP address is associated with a name that is only used as an internal reference within other sections of the studio configuration.

The default value is:
```json
"addresses": {
    "death": "192.168.56.20",
    "gambit": "192.168.56.143",
	"apocalypse": "192.168.56.74",

    "war": "192.168.56.24",
    "famine": "192.168.56.29",
    "pestilence": "192.168.56.4"
}
```

## Available Render Nodes
You can choose which render node the project should be deployed to. All machines that support being used as a render node are listed, and can be selected from when generating Switchboard config.

The default value is:
```json
"available_render_nodes": [
	"war",
	"famine",
	"pestilence"
]
```

## Render Cluster Configuration
> [!IMPORTANT]
> The render node configuration MUST match the nDisplay conifugration. It is recommended to NOT change the default render cluster configuration, this is included mainly for reference.

Each entry in the `render_nodes` array is a specific instance of Unreal corresponding to a node in the nDisplay configuration. Each node should have:
- `name`: The name of this node in the nDisplay configuration. It should match exactly.
- `config` [Optional]: A reference to one or more Render Node Configs (see below) to apply to this node. It should either be a string, in the case of a single configuration, or an array of strings, to apply multiple configurations to a single node.

The default config is:
```json
"render_nodes": [
    {
		"name": "OuterFrustum",
		"config": [
			"default",
			"high_performance"
		]
	},
	{
		"name": "InnerFrustum",
		"config": "default"
	},
	{
		"name": "Ceiling",
		"config": [
			"default",
			"high_performance"
		]
	}
]
```
### Render Node Config
Configuration profiles can be applied to individual render nodes. These apply collections of CVars to enable/disable/control rendering features of specific instances of Unreal. For example, turning off reflections and global illumination in the outer frustum, ceiling, and wild walls improves cluster performance with minimal reduction in perceived quality.

An example render node config is as follows:
```json
"render_node_config": {
    "default": {
        "cvars": [
            "r.Composure.CompositingElements.DisableActiveRendering=1",
            "CompUtils.CreateViewport=0"
        ]
    },
    "high_performance": {
        "cvars": [
            "r.VolumetricFog=0",
            "r.HeterogeneousVolumes=0",
            "r.DynamicGlobalIlluminationMethod=0",
            "r.ReflectionMethod=0"
        ]
    }
}
```
For example, `high_performance` is the look-up key for the configuration and should be used when referencing a config.

## Editor Configuration
Any number of machines can be specified to be used as editors. The format is similar to the render node config where each entry in the `control_nodes` array should contain:
- `name`: A user-friendly name for the instance of Unreal running the editor. Can be anything.
- `machine`: The physical machine the node should run on. Must be an entry within the `addresses` structure.

The default editor config will create one instance of an editor on DEATH:
```json
"control_nodes": [
    {
		"name": "Editor"
        "machine": "death",
    }
]
```

## LiveLinkHub Configuration
LiveLinkHub needs to be running on one of the machines to re-broadcast LiveLink data from the camera and camera tracking systems to all editors and render nodes.

A machine, that is an entry in the `addresses` structure, should be specified to determine which machine LiveLinkHub will run on. That machine should have a LiveLinkHub configuration set up and all of the required LiveLink plugins installed into LiveLinkHub.

The default LiveLinkHub configuration is:
```json
"livelinkhub": "death"
```
## FreeFileSync
FreeFileSync is used to mirror the project from the control machine onto the render machines.

The following options should be configured:
- `machine`: Which machine should FreeFileSync execute from. This should be the machine that has the master copy of the project (i.e. the control machine). It must be an entry from the `addresses` structure.
- `source_drive`: The drive on which the project resides. By default, this is the `D:` on DEATH. This is the drive that the project will be copied from.
- `dest_drives`: A mapping of machine names to drive letters that correspond to the network-mapped drives on the render nodes. These are the drives that the project files will be copied to, with the same relative path as the project has on the source drive. Every machine that can be used as a render node should be present.
- `path`: The filepath to the FreeFileSync application on the specified `machine`.

> [!IMPORTANT]
> It is recommended to not modify the `source_drive` and `dest_drives` - these have been set up (and network drives have been specifically mapped) in a way that nDisplay executes without issue.

The default FreeFileSync config is:
```json
"freefilesync": {
    "machine": "death",
    "path": "C:/Program Files/FreeFileSync/FreeFileSync.exe",
    "source_drive": "D:",
	"dest_drives": {
		"war": "W:",
		"famine": "Y:",
		"pestilence": "X:"
	}
}
```

## nDisplayTrace

nDisplayTrace allows for simultaneous profiling of all render nodes in the cluster and easy retrieval and analysis of the trace files.

The following options must be configured:
- `machine`: The machine that you want to anaylse trace data on. It must be an entry from the `addresses` structure.
- `name`: A user-friendly name for the device in Switchboard. It can be anything.
- `trace_store`: The local path on each render node where trace files are stored. Unreal Insights can then be configured to watch these directories to automatically pick up on new trace files.

The default trace configuration is:
```json
"trace": {
    "machine": "death",
    "name": "Trace",
    "trace_store": "D:/TRACE_STORE"
}
```

See [Profiling Guide](Profiling.md) for how to use the nDisplayTrace device.

## Reference
A full reference of the default `StudioProperties.json`:
```json
{
	"addresses": {
        "death": "192.168.56.20",
        "gambit": "192.168.56.143",
		"apocalypse": "192.168.56.74",

        "war": "192.168.56.24",
        "famine": "192.168.56.29",
        "pestilence": "192.168.56.4"
    },

	"available_render_nodes": [
		"war",
		"famine",
		"pestilence"
	],

    "control_nodes": [
        {
            "name": "Editor",
            "machine": "death"
        }
    ],

    "render_node_config": {
        "default": {
            "cvars": [
                "r.Composure.CompositingElements.DisableActiveRendering=1",
                "CompUtils.CreateViewport=0"
            ]
        },
        "high_performance": {
            "cvars": [
                "r.VolumetricFog=0",
                "r.HeterogeneousVolumes=0",
                "r.DynamicGlobalIlluminationMethod=0",
                "r.ReflectionMethod=0"
            ]
        }
    },

    "render_nodes": [
	    {
			"name": "OuterFrustum",
			"config": [
				"default",
				"high_performance"
			]
		},
		{
			"name": "InnerFrustum",
			"config": "default"
		},
		{
			"name": "Ceiling",
			"config": [
				"default",
				"high_performance"
			]
		}
    ],

	"freefilesync": {
        "machine": "death",
        "path": "C:/Program Files/FreeFileSync/FreeFileSync.exe",
        "source_drive": "D:",
		"dest_drives": {
			"war": "W:",
			"famine": "Y:",
			"pestilence": "X:"
		}
    },

	"trace": {
        "machine": "death",
        "name": "Trace",
        "trace_store": "D:/TRACE_STORE"
    },

    "livelinkhub": "death"
}
```