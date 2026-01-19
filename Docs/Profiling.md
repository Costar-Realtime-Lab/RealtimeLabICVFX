# Profiling
The nDisplayTrace device can be used to profile all render nodes in the nDisplay config simultaneously. The trace files are given useful filenames and stored on the render nodes, but can be easily accessed remotely from a control machine.

To start and stop profiling, use the "Start / Stop" profiling button on the nDispalyTrce device. **The nDisplay cluster must be running to begin profiling**.

If you have configured a trace store directory in `StudioProperties.json` then all trace files will be saved there (locally on each render node). If there is no trace store directory set, then trace files will be stored in the default directory within each project (`<Project Root>/Saved/Profiling/`).

The Insights frontend can be easily configured to automatically detect new trace files on the render node. Simply add the trace store directory on each render node into the Insights directory watchlist. For example, if I had the trace store set to `D:/TRACE_STORE` in `StudioProperties.json`, I can add the following additional directories for Insights to monitor:

![Insights Watchlist](InsightsWatchlist.png)