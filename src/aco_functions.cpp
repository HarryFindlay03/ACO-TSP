#include "../include/aco_functions.hpp"

// TODO
// Pheremone update

float tour_length(const matrix_t& D, int* tour, int num_cities)
{
    float res = 0;

    int i;
    for(i = 0; i < num_cities; i++)
        res += D[tour[i]][tour[i+1]];

    return res;
}

int shortest_tour(const matrix_t& D, int** ant_routes, int num_ants, int num_cities)
{
    int shortest = 0;
    int i;

    for(i = 1; i < num_ants; i++)
        if(tour_length(D, ant_routes[i], num_cities) < tour_length(D, ant_routes[shortest], num_cities))
            shortest = i;

    return shortest;
}

float city_pair_distance_heuristic(const matrix_t& D, int x, int y) { return 1 / D[x][y]; }

void generate_all_ant_routes(ANT_DATA* ant_data, int start_city, float alpha, float beta)
{
    int i;
    int num_ants = *(ant_data->num_ants);
    int num_cities = *(ant_data->num_cities);
     
    // for each ant
    for(i = 0; i < num_ants; i++)
        generate_ant_route(ant_data, i, start_city, alpha, beta);

    return;
}

void generate_ant_route(ANT_DATA* ant_data, int ant_num, int start_city, float alpha, float beta)
{
    int num_ants = *(ant_data->num_ants);
    int num_cities = *(ant_data->num_cities); 
    int* ant_route = (ant_data->ant_routes)[ant_num];
    ant_route[0] = start_city;

    int i = 1;
    while(i < num_cities)
    {
        int next = get_next_city(ant_data, ant_num, ant_route[i-1], alpha, beta);
        ant_route[i] = next;
        (ant_data->ant_map)[ant_num][next] = 1;
        i++;
    }

    ant_route[i] = ant_route[0];

    return;
}

int get_next_city(ANT_DATA* ant_data, int ant_num, int start_city, float alpha, float beta)
{
    int num_cities = *(ant_data->num_cities);
    int i;
    float probs[num_cities];

    for(i = 0; i < num_cities; i++)
        probs[i] = transition_rule(ant_data, ant_num, start_city, i, alpha, beta);

    int pos = 0;
    int remaining_cities[num_cities]; // only need ever be as big as num_cities
    float cumulative_probs[num_cities];
    float res = 0;
    for (i = 0; i < num_cities; i++)
    {
        if(probs[i])
        {
            remaining_cities[pos] = i;
            res += probs[i];
            cumulative_probs[pos] = res;
            pos++;
        }
    }

    // return which city to visit next 
    float spin = (float)rand() / RAND_MAX;
    i = 0;
    while (cumulative_probs[i] < spin)
        i++;

    return remaining_cities[i];
}

float transition_rule(ANT_DATA* ant_data, int ant_num, int city_i, int city_j, float alpha, float beta)
{
    if(city_i == city_j) return 0;

    int num_cities = *(ant_data->num_cities);
    const matrix_t& D = ant_data->D;
    matrix_t& T = ant_data->T;
    int* ant_tabu_table = (ant_data->ant_map)[ant_num];

    if(ant_tabu_table[city_j]) return 0;

    float nom, dom;

    nom = (std::pow(T[city_i][city_j], alpha)) * (std::pow(city_pair_distance_heuristic(D, city_i, city_j), beta));

    dom = 0;
    int h;
    for(h = 0; h < num_cities; h++)
    {
        // city h is unvisited
        if(!ant_tabu_table[h])
        {
            dom += (std::pow(T[city_i][h], alpha) * std::pow(city_pair_distance_heuristic(D, city_i, h), beta));
        }
    }

    return (nom / dom);
}

void lay_pheremones(ANT_DATA* ant_data, float Q)
{
    int num_ants = *(ant_data->num_ants);
    int num_cities = *(ant_data->num_cities);

    int i, j;
    for(i = 0; i < num_ants; i++)
    {
        int* ant_route = (ant_data->ant_routes)[i];
        float route_length = tour_length(ant_data->D, ant_route, num_cities);

        for(j = 0; j < num_cities; j++)
            (ant_data->T)[ant_route[j]][ant_route[j+1]] += (Q / route_length);
    }
}

void evaporate_pheremones(ANT_DATA* ant_data, float evaporation_rate)
{
    int num_ants = *(ant_data->num_ants);
    int num_cities = *(ant_data->num_cities);

    int i, j;

    // computing the quality heuristic
    float quality_heuristic = tour_quality_heuristic(ant_data->D, ant_data->ant_routes, num_ants, num_cities);

    // evaporate the pheremones
    for(i = 0; i < num_cities; i++)
    {
        for(j = 0; j < num_cities; j++)
        {
            if(i == j) continue; // do not evaporate i <-> i pairs
            float curr = (ant_data->T)[i][j];
            (ant_data->T)[i][j] = ((1 - evaporation_rate) * curr) + quality_heuristic;
        }
    }

    return;
}

float tour_quality_heuristic(const matrix_t& D, int** ant_routes, int num_ants, int num_cities)
{
    float res = 0;

    int i;
    for(i = 0; i < num_ants; i++)
        res += (1 / tour_length(D, ant_routes[i], num_cities));

    return res;
}


void prepare_new_run(ANT_DATA* ant_data, int start_city, float Q, float evaporation_rate)
{
    int num_ants = *(ant_data->num_ants);
    int num_cities = *(ant_data->num_cities);

    lay_pheremones(ant_data, Q);
    evaporate_pheremones(ant_data, evaporation_rate);
    reset_ant_tabu_tables(ant_data->ant_map, num_ants, num_cities, start_city);

    return;
}