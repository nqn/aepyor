# Aepyor

[![Build Status](https://travis-ci.org/nqn/aepyor.svg)](https://travis-ci.org/nqn/aepyor)

Aepyor is a flexible load generating Mesos framework to mimic real-life user and system behavior.

**NOTE:** This is still mostly an experimental workbench for generating the load patterns.

## Architecture

![Aepyor architecture](https://github.com/nqn/aepyor/raw/master/docs/images/architecture.png)

1. The initial load pattern will be driven by seasonal data model.
1. The result is pieces of work deltas which is described as a global QPS
   (Queries per second) for a given period of time.
1. This updates the scheduler global QPS goal
1. Initially, the goal QPS is sharded onto workers which gets a certain
   objective.
1. The worker reports the actual archivable QPS to the scheduler periodically.
1. The scheduler takes correcting actions to get closer to the target; either
   starting new workers and increase the projected goal or throttle projected
   goals and shut down workers.

## Building

```
mkdir build && cd build
cmake ..
make
make test
```

## Documentation

```
mkdir docs
doxygen
```

Documentation can then be found in `docs/html/index.html`.
