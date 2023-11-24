#include <cmath>
#include "aco_helper_functions.hpp"

float city_pair_distance_heuristic(float**, int, int);
int get_next_city(float**, float**, int*, int, int, int, float, float);
float transition_rule(float**, float**, int*, int, int, int, float, float);