//
// RELEVANT INCLUDES
//

#include <cmath>
#include <vector>

#include "aco_helper_functions.hpp"

//
// ANT ROUTE FUNCTIONS
//

/**
 * @brief returns the tour length of a given tour
 * 
 * @param D distance matrix
 * @param tour tour to find length of
 * @param num_cities number of cities in the optimisation
 * 
 * @return float 
 */
float tour_length(float**, int*, int);

/**
 * @brief returns the index of shortest tour given an array of tours
 * 
 * @param D distance matrix
 * @param ant_routes array of tours to consider
 * @param num_ants number of ants in the system
 * @param num_cities number of cities in the optimisation
 * 
 * @return int 
 */
int shortest_tour(float**, int**, int, int);

/**
 * @brief returns the city pair distance heuristic computed by 1 / distance between city x and city y
 * 
 * @param D distance matrix
 * @param x city x
 * @param y city y
 * 
 * @return float 
 */
float city_pair_distance_heuristic(float**, int, int);

/**
 * @brief generates all ant routes for a generation using transition rules and fills relevant information 
 * in ant_data struct
 * 
 * @param ant_data pointer to ant_data_t struct
 * @param start_city initial start position of ant agents
 * @param alpha parameter that weights importance of pheremone strength
 * @param beta parameter that weights the importance of the distance heuristic
 */
void generate_all_ant_routes(ANT_DATA*, int, float, float);

/**
 * @brief generate a single ant route given the ant from a given start city
 * 
 * @param ant_data pointer to ant_data_t struct
 * @param ant_num index of ant so correct tabu table can be gathered
 * @param start_city city to start route from
 * @param alpha parameter that weights importance of pheremone strength
 * @param beta parameter that weights importance of the distance heuristic
 */
void generate_ant_route(ANT_DATA*, int, int, float, float);

/**
 * @brief returns the next city to visit w.r.t the implemented transition rule
 * 
 * @param ant_data pointer to the ant_data_t struct
 * @param ant_num index of ant so correct tabu table can be gathered
 * @param current_city city to consider transition rule from
 * @param alpha parameter that weights importance of pheremone strength
 * @param beta parameter that weights importance of the distance heuristic
 * 
 * @return int 
 */
int get_next_city(ANT_DATA*, int, int, float, float);

//
// TRANSITION RULE
//

/**
 * @brief implements the transition rule of the ant system from Dorigo, Stutzle. 2004. Ant Colony Optimization.
 * Returns the probability of visiting city j from city i.
 * 
 * @param ant_data pointer to the ant_data_t struct
 * @param ant_num index of ant so correct tabu table can be gathered
 * @param city_i current city
 * @param city_j city to visit
 * @param alpha parameter that weights the importance of the pheremone strength
 * @param beta parameter that weights the importance of the distance heuristic
 * 
 * @return float 
 */
float transition_rule(ANT_DATA*, int, int, int, float, float);

//
// PHEREMONE FUNCTIONS
//

/**
 * @brief lays pheremones on pheremone matrix in ant_data according to Q / tour length of each ant
 * 
 * @param ant_data pointer to the ant_data_t struct
 * @param Q parameter that determines the amount of pheremone that is layed
 */
void deposit_pheremones(ANT_DATA*, float);

/**
 * @brief evaporates pheremones according to evaporation rule and quality heuristic from Dorigo, Stutzle. 2004. Ant Colony Optimization.
 * 
 * @param ant_data pointer to ant_data_t struct
 * @param evaporation_rate parameter affecting the amount of pheremone that is adapted
 */
void evaporate_pheremones(ANT_DATA*, float);

/**
 * @brief returns the value of the tour quality heuristic. Calculated by sum_k(1 / tour_length(ant_k))
 * 
 * @param D distance matrix
 * @param ant_routes array of tours to consider
 * @param num_ants number of ants in the system
 * @param num_cities number of cities in the optimisation
 * 
 * @return float 
 */
float tour_quality_heuristic(float**, int**, int, int);

/**
 * @brief updating pheremone matrix in ant_data, firstly by evaporating pheremones and then laying
 * pheremones using the ant routes in current generation and finally resetting tabu tables ready for
 * new generation
 * 
 * @param ant_data structure containing all ant data for metaheuristic
 * @param start_city integer value representing the city that current generation is starting from
 * @param Q parameter that determines how much pheremone is layed during lay_pheremones function
 * @param evaporation_rate parameter that determines how much pheremones evaporate
 */
void update_pheremones(ANT_DATA*, int, float, float);

//
// ELITIST ANT SYSTEM PHEREMONE FUNCTIONS
//

/**
 * @brief deposits pheremones according to elitist pheremone deposit rule from Dorigo, Stutzle. 2004. Ant Colony Optimization.
 * First deposits pheremones according to classic AS, so not to be used in conjunction with classic deposit_pheremones.
 * 
 * @param ant_data pointer to ant_data_t struct
 * @param shortest array containing the shortest tour found so far
 * @param e parmater affecting the amount of additional reinforcement added to T^(bs), a good initial value e = num_cities
 * @param Q parameter affecting the amount of pheremone to be deposited during lay_pheremone. 
 */
void deposit_pheremones_elitist(ANT_DATA*, int*, float, float);

/**
 * @brief updates pheremone matrix in ant_data by following same functionality as classic update_pheremones with added
 * elitist functionality.
 * 
 * @param ant_data structure containing all ant data for metaheuristic
 * @param shortest array containing the shortest tour found so far
 * @param start_city integer value representing the city that current generation is starting from
 * @param e parameter affecting the amount of additional reinforcement added to T^(bs), a good initial value e = num_cities
 * @param Q parameter affecting the amount of pheremone to be deposited during lay_pheremone.
 * @param evaporation_rate parameter that determines how much pheremones evaporate
 */
void update_pheremones_elitist(ANT_DATA*, int*, int, float, float, float);