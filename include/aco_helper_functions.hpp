#ifndef ACO_HELPER_FUNCTIONS_H

#define ACO_HELPER_FUNCTIONS_H

#include <iostream>
#include <map>
#include <cstdlib>
#include <vector>

#include "../ext/pugixml/pugixml.hpp"

typedef std::vector<std::vector<float> > matrix_t;

typedef struct ant_data_t {
    const matrix_t& D;
    matrix_t& T;
    int** ant_map;
    int** ant_routes;
    int* num_ants;
    int* num_cities;

    ant_data_t(const matrix_t& D, matrix_t& T) : D(D), T(T) {}
} ANT_DATA;

ANT_DATA* generate_ant_data(char*, int, int);
const matrix_t& generate_distance_matrix(char*, int);
matrix_t& generate_pheremone_matrix(int);
int** generate_ant_tabu_tables(int, int, int);
void reset_ant_tabu_tables(int**, int, int, int);
int** generate_initial_ant_routes(int, int);
int get_num_cities(char*);

#endif