
# sdlprof: Storage DL Profiler
### Set up sdlprof
```shell
$ git clone git@github.com:mariabeatrizmo/sdlprof.git
$ cd Profiler
$ mkdir build; cd build
$ cmake ..
$ cmake --build .
$ export PROFILING_DIR=$(pwd)/libprofiler.so
```

### Using sdlprof
```shell
$ LD_PRELOAD=$PROFILING_DIR ./executable
```

### Configurations
Basic configurations can be found in the file `include/config.hpp`.

- `log_type` defines if the log file created will be written in JSON format or in a format destined to easy for people to read.
- `dir` specifies the path where the log file will be created.
- `machine_name` specifies the name of the machine where the program is running (this is used as part of the log name). If left empty, the program sets it to the value of the hostname.
- `log_name` specifies the name of the log file. If left empty the log file will be "log_D.F" where "D" is the datetime of creation of the log file and "F" it's extension (depends on the log_type choosen).
- `reset_pid_per_op` is a flag that specifies if the PIP is always rechecked at every operation intercepted (!=0), or if it's not necessary to do so (==0).

### Example 
``` shell
$ git clone git@github.com:mariabeatrizmo/sdlprof.git
$ cd Profiler
$ mkdir build; cd build
$ cmake ..
$ cmake --build .
$ export PROFILER=$(pwd)/libprofiler.so
$ cd ../test
$ g++ -g -o main main.cpp -ldl
$ LD_PRELOAD=$PROFILER ./main
```
