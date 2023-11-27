#ifndef ACO_HELPER_FUNCTIONS_H
#define ACO_HELPER_FUNCTIONS_H

#include <iostream>
#include <map>
#include <cstdlib>
#include "../ext/pugixml/pugixml.hpp"

typedef std::map<int, int*> ant_tabu_map_t;

typedef struct ant_data_t {
    float** D;
    float** T;
    ant_tabu_map_t ant_map;
} ANT_DATA;

ANT_DATA* generate_ant_data(char*, int, int, int);
float** generate_distance_matrix(char*, int);
float** generate_pheremone_matrix(int);
ant_tabu_map_t generate_ant_tabu_tables(int, int, int);

#endif