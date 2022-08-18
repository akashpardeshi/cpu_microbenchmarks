# cpu_microbenchmarks

This repository contains code for exploring the microarchitecture of ARMv8-A based CPUs through writing microbenchmarks.

# Current Microbenchmarks
* Branch prediction
    - branch target buffer capacity and associativity
    - return address stack capacity
* Memory subsystem
    - cache line size
    - translation lookaside buffer capacity and associativity

# Usage
The microbenchmarks can be run to produce graphs with Python's `matplotlib` or raw data to stdout to be plotted manually (for non-automated tests). To run a microbenchmark, `cd` into its directory, then compile and run as follows:
```
make name

# for graphical output
./name | python3 ../plot.py

# for text output
./name
```

Note: both branch target buffer micromenchmarks are currently non-automated.
