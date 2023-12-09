CC = g++

all: aco_driver

generate_folder_structure:
	if [ ! -d build ]; then mkdir -p build; fi; if [ ! -d bin ]; then mkdir -p bin; fi

aco_driver.o:
	g++ -c src/aco_driver.cpp -o build/aco_driver.o

aco_functions.o:
	g++ -c src/aco_functions.cpp -o build/aco_functions.o

aco_helper_functions.o: 
	g++ -c  src/aco_helper_functions.cpp -o build/aco_helper_functions.o

pugixml.o:
	g++ -c ext/pugixml/pugixml.cpp -o build/pugixml.o

aco_driver: generate_folder_structure aco_driver.o aco_functions.o aco_helper_functions.o pugixml.o
	g++ -o bin/aco_driver build/aco_driver.o build/aco_functions.o build/aco_helper_functions.o build/pugixml.o


