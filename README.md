# Ant Colony Optimisation TSP Solver
This repo provides all the provided files to run this implementation of ACO on the provided TSP instances (found in /data).

### Running the Program
**Prerequisites**
To compile the program using the `Makefile` provided you need a working version of GCC installed, or be able to run the `g++` compiler.

### Steps to Compile
1) Open a terminal instance, and ensure that you have navigated to the root of this project (when running a command anagalous to `pwd` it should say `<blah...blah>/ACO_TSP`)
2) Run the `make` command or alternatively `make aco_driver` in your terminal. This will create all the necessary directories, object files, and the final executable for you ! (Although if this does not work, one can follow the steps at the bottom of this readme...)
3) Once you have have completed (2) please move to the next section!

### Using the Executable
Once you have successfully compiled the program, you will be able to find the executable in the `bin` directory, the executable will be called `aco_driver` if you have used the `make aco_driver` rule.

To run the program on *MacOS* or *Linux* you can use the below command (if you are in the root of the ACO_TSP directory)
```
./bin/aco_driver <path_to_TSP_instance> <path_to_parameter_file>
```

`<path_to_TSP_instance>` - this is the location of the file containing TSPLIB TSP instance data, two examples have been provided in `/data`. This is a **compulsary** argument to pass but don't worry the program will bug you to enter a valid path if you do not!

`<path_to_parameter_file>` - this is the location of the file containing parameter information, an example has also been provided in `/data`. This is an **optional** argument and if not passed, the program will use default values that are defined in the code ... you can of course change these if you are brave, but you cannot blame me if they then break ! More information on the parameter file can be found in the next section

**Example commands:**
If you just want to run the program nice and easy here are two example you can paste into your terminal if you are currently in the ACO_TSP root (`<blah...blah>/ACO_TSP`)
```
./bin/aco_driver data/burma14.xml data/param_file.txt
```

```
./bin/aco_driver data/brazil58.xml
```

### The Parameters File
The parameters file is simply a text file (with a very **specific** format!) that the executable can read from so that a user can specify any values for the parameters that they may like!

An example parameters file has been provided in this repo and can be found here - `data/param_file.txt`. An example of its contents has also been provided below.

```
num_ants=20
alpha=1
beta=3
Q=1
evaporation_rate=0.3
iterations=10000
T0_heuristic=1
approach=0
retries=3
```

*Note - please ensure if you edit this file to change any parameter values, that there is **no** whitespace and that the order of the parameters stays **exactly** as above*.

