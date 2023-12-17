# Ant Colony Optimisation on TSP

This repo provides all the provided files to run this implementation of ACO on the provided TSP instances (found in /data).

### Running the Program

**Prerequisites**
- An installation of GCC to be able to make and run the program

This implementation has been developed using gcc version `clang-1400.0.29.202`.

**Building and Running**

This repo provides a Makefile that allows the program to be built and ran using one command.

>``make run``

will create the required directories, build the program, and run the program. This is the easiest way to do it!

>``make || make aco_driver``

will build the program, you will then be required to run the program. Note that the final executable can be found in /bin and the data files are stored in .../data/*.xml so to ensure the program runs smoothly please run the executable from the root of this project (.../ACO_TSP/). This can be achieved by running ./bin/aco_driver. (However, `make run` is easier.)
