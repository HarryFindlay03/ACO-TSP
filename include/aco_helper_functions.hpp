#ifndef ACO_HELPER_FUNCTIONS_H

#define ACO_HELPER_FUNCTIONS_H

#include <iostream>
#include <map>
#include <cstdlib>

#include "../ext/pugixml/pugixml.hpp"

typedef struct ant_data_t {
    float** D;
    float** T;
    int** ant_map;
    int** ant_routes;
    int* num_ants;
    int* num_cities;
} ANT_DATA;

ANT_DATA* generate_ant_data(char*, int, int, int);
float** generate_distance_matrix(char*, int);
float** generate_pheremone_matrix(int);
int** generate_ant_tabu_tables(int, int, int);
void reset_ant_tabu_tables(int**, int, int, int);
int** generate_initial_ant_routes(int, int);

#endif