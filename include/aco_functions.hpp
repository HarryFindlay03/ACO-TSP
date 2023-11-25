#include <cmath>
#include <vector>
#include "aco_helper_functions.hpp"

float city_pair_distance_heuristic(float**, int, int);
int** generate_all_ant_routes(float**, float**, ant_tabu_map_t, int, int, int, float, float);
int* generate_ant_route(float**, float**, int*, int, int, float, float);
int get_next_city(float**, float**, int*, int, int, float, float);
float transition_rule(float**, float**, int*, int, int, int, float, float);