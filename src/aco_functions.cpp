#include "../include/aco_functions.hpp"

// TODO
// Pheremone update

float tour_length(float** D, int* tour, int num_cities)
{
    float res = 0;

    int i;
    for(i = 0; i < num_cities; i++)
        res += D[tour[i]][tour[i+1]];

    return res;
}

float city_pair_distance_heuristic(float** D, int x, int y) { return 1 / D[x][y]; }

void generate_all_ant_routes(ANT_DATA* ant_data, int num_ants, int num_cities, int start_city, float alpha, float beta)
{
    int i;
     
    // for each ant
    for(i = 0; i < num_ants; i++)
        generate_ant_route(ant_data, i, num_cities, start_city, alpha, beta);

    return;
}

void generate_ant_route(ANT_DATA* ant_data, int ant_num, int num_cities, int start_city, float alpha, float beta)
{
    int* ant_route = (ant_data->ant_routes)[ant_num];
    ant_route[0] = start_city;

    int i = 1;
    while(i < num_cities)
    {
        int next = get_next_city(ant_data, ant_num, num_cities, ant_route[i-1], alpha, beta);
        ant_route[i] = next;
        (ant_data->ant_map)[ant_num][next] = 1;
        i++;
    }

    ant_route[i] = ant_route[0];

    return;
}

int get_next_city(ANT_DATA* ant_data, int ant_num, int num_cities, int start_city, float alpha, float beta)
{
    int i;
    float probs[num_cities];

    for(i = 0; i < num_cities; i++)
        probs[i] = transition_rule(ant_data, ant_num, num_cities, start_city, i, alpha, beta);

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

float transition_rule(ANT_DATA* ant_data, int ant_num, int num_cities, int city_i, int city_j, float alpha, float beta)
{
    if(city_i == city_j) return 0;

    float** D = ant_data->D;
    float** T = ant_data->T;
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

void lay_pheremones(ANT_DATA* ant_data, int num_ants, int num_cities, float Q)
{
    int i, j;
    for(i = 0; i < num_ants; i++)
    {
        int* ant_route = (ant_data->ant_routes)[i];
        float route_length = tour_length(ant_data->D, ant_route, num_cities);

        for(j = 0; j < num_cities; j++)
            (ant_data->T)[ant_route[j]][ant_route[j+1]] += (Q / route_length);
    }
}

void prepare_new_run(ANT_DATA* ant_data, int num_ants, int num_cities, int start_city, float Q)
{
    lay_pheremones(ant_data, num_ants, num_cities, Q);
    ant_data->ant_map = generate_ant_tabu_tables(num_ants, num_cities, start_city);
}