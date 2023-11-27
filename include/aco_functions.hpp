#include <cmath>
#include <vector>

#include "aco_helper_functions.hpp"

float tour_length(float**, int*, int);
float city_pair_distance_heuristic(float**, int, int);
void generate_all_ant_routes(ANT_DATA*, int, int, int, float, float);
void generate_ant_route(ANT_DATA*, int, int, int, float, float);
int get_next_city(ANT_DATA*, int, int, int, float, float);
float transition_rule(ANT_DATA*, int, int, int, int, float, float);
void lay_pheremones(ANT_DATA*, int, int, float);