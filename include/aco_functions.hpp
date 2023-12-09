#include <cmath>
#include <vector>

#include "aco_helper_functions.hpp"

float tour_length(const matrix_t&, int*, int);
int shortest_tour(const matrix_t&, int**, int, int);
float city_pair_distance_heuristic(float**, int, int);
void generate_all_ant_routes(ANT_DATA*, int, float, float);
void generate_ant_route(ANT_DATA*, int, int, float, float);
int get_next_city(ANT_DATA*, int, int, float, float);
float transition_rule(ANT_DATA*, int, int, int, float, float);
void lay_pheremones(ANT_DATA*, float);
void evaporate_pheremones(ANT_DATA*, float);
float tour_quality_heuristic(const matrix_t&, int**, int, int);
void prepare_new_run(ANT_DATA*, int, float, float);