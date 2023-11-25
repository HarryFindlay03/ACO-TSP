#include <iostream>
#include <map>
#include <cstdlib>
#include "../ext/pugixml/pugixml.hpp"

typedef std::map<int, int*> ant_tabu_map_t;

float** generate_distance_matrix(char*, int);
float** generate_pheremone_matrix(int);
ant_tabu_map_t generate_ant_tabu_tables(int, int, int);