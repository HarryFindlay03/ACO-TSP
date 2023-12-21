#ifndef ACO_HELPER_FUNCTIONS_H

#define ACO_HELPER_FUNCTIONS_H

// relevant includes

#include <iostream>
#include <map>
#include <cstdlib>
#include <vector>

#include "../ext/pugixml/pugixml.hpp"

//
// typedef struct
//

/**
 * @brief ant_data_t structure that stores all relevant information about ant
 * 
 * @param D distance matrix
 * @param T pheremone matrix
 * @param ant_map ant tabu tables
 * @param ant_routes current ant routes
 * @param num_ants number of ants in the system
 * @param num_cities number of cities in the optimisation
 */
typedef struct ant_data_t {
    float** D;
    float** T;
    int** ant_map;
    int** ant_routes;
    int* num_ants;
    int* num_cities;
} ANT_DATA;

//
// ANT SYSTEM SETUP FUNCTIONS
//

/**
 * @brief generates and returns necessary ant data
 * 
 * @param filename string representing filename (location of file from root of program execution)
 * @param num_ants number of ants in the system
 * @param num_cities number of cities in the optimisation
 * @param use_heuristic (optional) if false then random number between 0 and 1 set for each pos in pheremone matrix.
 * If true, nearest neighbour heuristic is used.
 * 
 * @return ANT_DATA*
 */
ANT_DATA* generate_ant_data(const char*, int, int, int use_heuristic=1);

/**
 * @brief generate and returns distance matrix given filename and number of cities in the given input file
 * 
 * @param filename string representing filename (location of file from root of program)
 * @param num_cities number of cities in the given file
 * 
 * @return float** - 2D array that stores distance matrix for given file
 */
float** generate_distance_matrix(const char*, int);

/**
 * @brief generate and return pheremone matrix given a distance matrix and number of cities in distance matrix
 * 
 * @param D distance matrix
 * @param num_ants number of ants in the system
 * @param num_cities number of cities in distance matrix
 * @param use_heuristic (optional) if false then random number between 0 and 1 set for each pos in pheremone matrix.
 * If true, nearest neighbour heuristic is used.
 * 
 * @return float**
 */
float** generate_pheremone_matrix(float**, int, int, int use_heuristic=1);

/**
 * @brief generate and return initial ant tabu tables
 * 
 * @param num_ants number of ants in the system
 * @param num_cities number of cities in the optimisation
 * 
 * @return int**
 */
int** generate_ant_tabu_tables(int, int);

/**
 * @brief reset the ant tabu tables to correct starting values w.r.t start city
 * 
 * @param ant_tabu_tables pointer to ant tabu tables
 * @param num_ants number of ants in the system
 * @param num_cities number of cities in the optimisation
 * @param start_city city to start the run from (these are intially set to visited in this function)
 * 
 */
void reset_ant_tabu_tables(int**, int, int, int);

/**
 * @brief generate and return initial ant routes
 * 
 * @param num_ants number of ants in the system
 * @param num_cities number of cities in the optimisation
 * 
 * @return int**
 */
int** generate_initial_ant_routes(int, int);

/**
 * @brief return the number of cities in a given file
 * 
 * @param filename file to get number of cities from
 * 
 * @return int
 */
int get_num_cities(const char*);

//
// NEAREST NEIGHBOUR HEURISTIC
//

/**
 * @brief returns the length of a nearest neighbour heuristic tour from a given start city
 * 
 * @param D distance matrix
 * @param num_cities number of cities in distance matrix
 * @param start_city city to start NN heuristic from
 * 
 * @return float
 */
float nearest_neighbour_tour_length(float**, int, int);

/**
 * @brief return the next city to visit using NN heuristic logic, i.e. the city with the shortest edge
 * from the current city.
 * 
 * @param D distance matrix
 * @param visited cities that have already been visited
 * @param num_cities number of cities in the optimisation
 * @param curr_city city to find next city from
 * 
 * @return int
 */
int nearest_neighbour_get_next_city(float**, int*, int, int);

/**
 * @brief find the shortest nearest neighbour tour by starting the tour from each possible city given
 * the distance matrix.
 * 
 * @param D distance matrix
 * @param num_cities number of cities in the optimisation
 * 
 * @return float
 */
float shortest_nn_tour(float**, int);

/**
 * @brief return the tour length of a given tour
 * 
 * @param D distance matrix
 * @param tour tour to find distance of
 * @param num_cities number of cities in the optimisation
 * 
 * @return float
 */
float helper_tour_length(float**, int*, int);

// VALIDITY CHECKS
/**
 * @brief Checking that a given tour is valid and only visits each city once
 * 
 * @param tour: tour to check validity of
 * @param num_cities: number of cities in the input 
 * @return int (boolean)
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
 * @return int (boolean)
 */
int copy_shortest(float**, int*, int*, int);

/**
 * @brief freeing all memory associated with ant_data
 * 
 * @param ant_data structure to be freed
 */
void clean_up(ANT_DATA* ant_data);

#endif