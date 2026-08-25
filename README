# STARCH-monitor

## Dependencies

### Mochi-Margo 
Please use [this branch](https://github.com/klasalx/mochi-margo/tree/load-monitor-library) of Mochi-Margo for installation. 
Mochi-Margo depends on Mercury and Argobots. 

```bash
git clone https://github.com/klasalx/mochi-margo.git
cd mochi-margo
git checkout 642c370
```

Then follow the build instructions. A basic build might look like this:
```bash
cd mochi-margo
mkdir build && cd build
cmake ..
make
make install
```

### LTTng (LTTng-ust, LTTng-tools) 
Follow build instructions:
https://lttng.org/docs/v2.15/#doc-installing-lttng

## Build
```bash
mkdir build && cd build
cmake ..
make
```

## Usage
Before any Mochi Margo client/server initialization, the environment variable ```MARGO_MONITOR_LIBRARY``` has to be exported and point to the `starch_monitor.so` generated during the build phase. These environment variables may need to be forwarded for distributed execution (typically using `-x`). An LTTng session has to be running on every target machine, configured to accept the following traces:

```
margo_core:init    (required)
margo_rpc:register (required)
margo_rpc:*        (recommended)
```

A basic lttng initialization script might look like this:
```
OUTDIR="/path/to/dir"
NODEID=$(hostname)
SESSION="test-session-$NODEID"

lttng-sessiond --daemonize

lttng create $SESSION --output=$OUTDIR/$NODEID
lttng enable-event --session=$SESSION --userspace 'margo_core:init'
lttng enable-event --session=$SESSION --userspace 'margo_rpc:*'
lttng enable-event --session=$SESSION --userspace 'margo_bulk:*'
lttng add-context --session=$SESSION --userspace --type=vpid
lttng add-context --session=$SESSION --userspace --type=vtid
lttng start $SESSION
```
