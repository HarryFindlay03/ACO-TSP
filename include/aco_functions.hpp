#include <cmath>
#include <vector>

#include "aco_helper_functions.hpp"

float tour_length(float**, int*, int);
int shortest_tour(float**, int**, int, int);
float city_pair_distance_heuristic(float**, int, int);
void generate_all_ant_routes(ANT_DATA*, int, float, float);
void generate_ant_route(ANT_DATA*, int, int, float, float);
int get_next_city(ANT_DATA*, int, int, float, float);
float transition_rule(ANT_DATA*, int, int, int, float, float);
void lay_pheremones(ANT_DATA*, float);
void evaporate_pheremones(ANT_DATA*, float);
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