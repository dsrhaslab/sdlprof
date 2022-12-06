
# sdlprof: Storage DL Profiler
### Set up sdlprof
```shell
$ git clone https://github.com/dsrhaslab/sdlprof.git
$ cd sdlprof
$ mkdir build; cd build
$ cmake ..
$ cmake --build .
$ export PROFILER=$(pwd)/libprofiler.so
```

### Using sdlprof
```shell
$ LD_PRELOAD=$PROFILER ./executable
```

### Configurations
Basic configurations can be found in the file `include/config.hpp`.

- `log_type` defines if the log file created will be written in JSON format or in a format destined to easy for people to read.
- `dir` specifies the path where the log file will be created.
- `hostname` specifies the name of the machine where the program is running (this is used as part of the log name). If left empty, the program sets it to the value of the hostname.
- `log_file_name` specifies the name of the log file. If left empty the log file will be "log_M_D.F" where 'M' is `hostname`, 'D' is the datetime of creation of the log file and "F" it's extension (depends on the `log_type` choosen).
- `reset_pid_per_op` is a flag that specifies if the PIP is always rechecked at every operation intercepted (true), or if it's not necessary to do so (false).

### Example 
To run the test main.cpp with sdlprof execute the following commands.
``` shell
$ cd ../test
$ g++ -g -o main main.cpp -ldl
$ LD_PRELOAD=$PROFILER ./main
```

The content of the log file obtained must be similar to the bellow.
```json
{"sys_call_name":"open","timestamp":1669711420837207,"path":"../include/config.hpp","result":3,"pid":332680}
{"sys_call_name":"open","timestamp":1669711420837571,"path":"copy.py","result":4,"pid":332680}
{"sys_call_name":"read","timestamp":1669711420837606,"fd":3,"counter":256,"result":256,"pid":332680}
{"sys_call_name":"write","timestamp":1669711420837659,"fd":4,"counter":256,"result":256,"pid":332680}
{"sys_call_name":"read","timestamp":1669711420837722,"fd":3,"counter":256,"result":13,"pid":332680}
{"sys_call_name":"write","timestamp":1669711420837756,"fd":4,"counter":13,"result":13,"pid":332680}
{"sys_call_name":"read","timestamp":1669711420837794,"fd":3,"counter":256,"result":0,"pid":332680}
{"sys_call_name":"close","timestamp":1669711420837833,"fd":3,"result":0,"pid":332680}
{"sys_call_name":"close","timestamp":1669711420837859,"fd":4,"result":0,"pid":332680}
{"sys_call_name":"mmap","timestamp":1669711420837880,"addr":"0","length":20,"prot":3,"flags":34,"fd":0,"offset":0,"pid":332680}
{"sys_call_name":"munmap","timestamp":1669711420837990,"addr":"0x7fcebe62e000","length":40,"result":0,"pid":332680}
```
