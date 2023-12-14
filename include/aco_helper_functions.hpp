#ifndef ACO_HELPER_FUNCTIONS_H

#define ACO_HELPER_FUNCTIONS_H

#include <iostream>
#include <map>
#include <cstdlib>
#include <vector>

#include "../ext/pugixml/pugixml.hpp"

typedef struct ant_data_t {
    float** D;
    float** T;
    int** ant_map;
    int** ant_routes;
    int* num_ants;
    int* num_cities;
} ANT_DATA;

ANT_DATA* generate_ant_data(const char*, int);
float** generate_distance_matrix(const char*, int);
float** generate_pheremone_matrix(float**, int);
int** generate_ant_tabu_tables(int, int);
void reset_ant_tabu_tables(int**, int, int, int);
int** generate_initial_ant_routes(int, int);
int get_num_cities(const char*);

// NEAREST NEIGHBOUR HEURISTIC
float nearest_neighbour_tour_length(float**, int, int);
int nearest_neighbour_get_next_city(float**, int*, int, int);
float shortest_nn_tour(float**, int);
float helper_tour_length(float**, int*, int);

// VALIDITY CHECKS
/**
 * @brief Checking that a given tour is valid and only visits each city once
 * 
 * @param tour: tour to check validity of
 * @param num_cities: number of cities in the input 
 * @return boolean true for if tour is valid false otherwise 
 */
int tour_valid(int*, int);

// MISC HELP FUNCTIONS

/**
 * @brief Copy generations shortest route into shortest if generations shortests tour is shorter
 * 
 * @param D distance matrix
 * @param shortest previous shortest route
 * @param generation_shortest new shortest route to be copied
 * @param num_cities number of cities:w
 * 
 * @return true if generation_shortest is copied into shortest, false otherwise
 */
int copy_shortest(float**, int*, int*, int);

/**
 * @brief freeing all memory associated with ant_data
 * 
 * @param ant_data structure to be freed
 */
void clean_up(ANT_DATA* ant_data);

#endif