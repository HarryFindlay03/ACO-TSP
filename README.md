# Ant Colony Optimisation TSP Solver
This repo provides all the provided files to run this implementation of ACO on the provided TSP instances (found in /data).

### Running the Program
**Prerequisites**
To compile the program using the `Makefile` provided you need a working version of GCC installed, or be able to run the `g++` compiler.

Please also note that this readme is written for UNIX/MACOS/Linux type operating systems, it will still work for windows, you will just have to use the Windows specific commands.

### Steps to Compile
1) Open a terminal instance, and ensure that you have navigated to the root of this project (when running a command anagalous to `pwd` it should say `.../ACO_TSP`)
2) Run the `make aco_driver` command in your terminal. This will create all the necessary directories, object files, and the final executable for you ! (Although if this does not work, one can follow the steps at the bottom of this readme...)
3) Once you have have completed (2) please move to the next section!

### Using the Executable
Once you have successfully compiled the program, you will be able to find the executable in the `bin` directory, the executable will be called `aco_driver` if you have used the `make aco_driver` rule.

To run the program on *MacOS* or *Linux* you can use the below command (if you are in the root of the ACO_TSP directory)
```
./bin/aco_driver <path_to_TSP_instance> <path_to_parameter_file>
```

`<path_to_TSP_instance>` - this is the location of the file containing TSPLIB TSP instance data, two examples have been provided in `/data`. This is a **compulsary** argument to pass but don't worry the program will bug you to enter a valid path if you do not!

`<path_to_parameter_file>` - this is the location of the file containing parameter information, an example has also been provided in `/data`. This is an **optional** argument and if not passed, the program will use default values that are defined in the code.  More information on the parameter file can be found in the relevantly titled section.

**Example commands:**

If you just want to run the program nice and easy here are two example you can paste into your terminal if you are currently in the ACO_TSP root (`.../ACO_TSP`) and have compiled the project.
```
./bin/aco_driver data/burma14.xml data/param_file.txt
```

The above command will run ACO on the burma14 TSP instance using parameter values taken from the parameter file found at `/data/param_file.txt`.

```
./bin/aco_driver data/brazil58.xml
```

This above command will run ACO on the brazil58 TSP instance using the default values defined in the code.

### The Parameters File
The parameters file is simply a text file (with a very **specific** format!) that the executable can read from so that a user can specify any values for the parameters that they may like!

An example parameters file has been provided in this repo and can be found here - `data/param_file.txt`. An example of its contents has also been provided below.

```
num_ants=20
alpha=1
beta=3
Q=1
evaporation_rate=0.3
iterations=3000
T0_heuristic=1
approach=0
retries=1
```

*Note - please ensure if you edit this file to change any parameter values, that there is **no** whitespace and that the order of the parameters stays **exactly** as above*.

**What do the parameters mean?**
- `num_ants={1, 100}` -> The number of ants in the colony
- `alpha={0.5-1.5}` -> This parameter affects the weighting of the pheremone level
- `beta={2-10}` -> This parameter affects the weighting of the distance heuristic
- `Q={1-10}` -> This parameter affects the return of the distance heuristic
- `evaporation_rate={0.1-1}` -> This parameter affects the evaporation rate
- `iterations={1-10000}` -> The number of iterations the ant colony optimisation will run for
- `T0_heuristic={0,1}` -> Set to 1 (True) for the nearest neighbour heuristic to be used to initialise pheromones
- `approach={0,1}` -> Set to 0 to use *classic* ant system, alternatively set to 1 to use *elitist* ant system
- `retries={1,100}` -> The number of times the entire ant colony optimisation will be run for

### Compiling Without the Makefile
First we need to create a `bin` folder and an `include` folder in the root directory
```
mkdir bin
mkdir build
```

Next we need to compile all of the required programs in the order as below
```
g++ -c src/aco_driver.cpp -o build/aco_driver.o
g++ -c src/aco_experiment_functions.cpp -o build/aco_experiment_functions.o
g++ -c src/aco_functions.cpp -o build/aco_functions.o
g++ -c src/aco_helper_functions.cpp -o build/aco_helper_functions.o
g++ -c ext/pugixml/pugixml.cpp -o build/pugixml.o
```

Once all of these have been successfully compiled, we can now compile the main executable with the following command
```
g++ -o bin/aco_driver build/aco_driver.o build/aco_experiment_functions.o build/aco_functions.o build/aco_helper_functions.o build/pugixml.o
```

This will place the executable in the folder `/bin` and the executable will be named `aco_driver`. You can then run the executable!


