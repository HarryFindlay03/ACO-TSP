#include "../include/aco_functions.hpp"

// TODO - rewrite get_next_city function

//
// ANT ROUTE FUNCTION
//

float tour_length(float** D, int* tour, int num_cities)
{
    float res = 0;

    int i;
    for(i = 0; i < num_cities-1; i++)
        res += D[tour[i]][tour[i+1]];
    res += D[tour[i]][tour[0]];

    return res;
}

int shortest_tour(float** D, int** ant_routes, int num_ants, int num_cities)
{
    int shortest = 0;
    
    int i;
    for(i = 1; i < num_ants; i++)
    {
        int* ant_route = ant_routes[i];
        int* curr_shortest = ant_routes[shortest];

        if(tour_length(D, ant_route, num_cities) < tour_length(D, curr_shortest, num_cities))
        {
            shortest = i;
        }
    }

    return shortest;
}

float city_pair_distance_heuristic(float** D, int x, int y, float Q) { return Q / D[x][y]; }

void generate_all_ant_routes(ANT_DATA* ant_data, int start_city, float alpha, float beta, float Q)
{
    int i;
    int num_ants = *(ant_data->num_ants);
    int num_cities = *(ant_data->num_cities);

    // prepare ant tabu tables for new generation
    reset_ant_tabu_tables(ant_data->ant_map, num_ants, num_cities, start_city);
     
    // for each ant
    for(i = 0; i < num_ants; i++)
        generate_ant_route(ant_data, i, start_city, alpha, beta, Q);

    return;
}

void generate_ant_route(ANT_DATA* ant_data, int ant_num, int start_city, float alpha, float beta, float Q)
{
    int num_ants = *(ant_data->num_ants);
    int num_cities = *(ant_data->num_cities); 
    int* ant_route = (ant_data->ant_routes)[ant_num];

    ant_route[0] = start_city;

    int i;
    for(i = 0; i < num_cities-1; i++)
    {
        int next = get_next_city(ant_data, ant_num, ant_route[i], alpha, beta, Q);
        
        // updating current ant route and ant tabu table
        ant_route[i+1] = next;
        (ant_data->ant_map)[ant_num][next] = 1;
    }

    return;
}

int get_next_city(ANT_DATA* ant_data, int ant_num, int current_city, float alpha, float beta, float Q)
{
    int num_cities = *(ant_data->num_cities);
    int i;
    float* probs = new float[num_cities];

    for(i = 0; i < num_cities; i++)
        probs[i] = transition_rule(ant_data, ant_num, current_city, i, alpha, beta, Q);

    int pos = 0;
    int* remaining_cities = new int[num_cities]; // only need ever be as big as num_cities
    float* cumulative_probs = new float[num_cities];
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

    int res_return = remaining_cities[i];
    
    delete[] probs;
    delete[] remaining_cities;
    delete[] cumulative_probs;

    return res_return;
}

//
// TRANSITION RULE
//

float transition_rule(ANT_DATA* ant_data, int ant_num, int city_i, int city_j, float alpha, float beta, float Q)
{
    int num_cities = *(ant_data->num_cities);
    float** D = ant_data->D;
    float** T = ant_data->T;
    int* ant_tabu_table = (ant_data->ant_map)[ant_num];

    // TEST CASES
    if(city_i == city_j) return 0; // trying to visit the same city
    if(ant_tabu_table[city_j]) return 0; // if next city to visit is already visited

    float nom, dom;

    nom = (std::pow(T[city_i][city_j], alpha)) * (std::pow(city_pair_distance_heuristic(D, city_i, city_j, Q), beta));

    dom = 0;
    int h;
    for(h = 0; h < num_cities; h++)
    {
        // city h is unvisited
        if(!ant_tabu_table[h])
        {
            dom += (std::pow(T[city_i][h], alpha) * std::pow(city_pair_distance_heuristic(D, city_i, h, Q), beta));
        }
    }

    return (nom / dom);
}

//
// PHEREMOME FUNCTIONS
//

void deposit_pheremones(ANT_DATA* ant_data, float Q)
{
    int num_ants = *(ant_data->num_ants);
    int num_cities = *(ant_data->num_cities);

    int i, j;
    for(i = 0; i < num_ants; i++)
    {
        int* ant_route = (ant_data->ant_routes)[i];
        float deposit_amount = (Q / tour_length(ant_data->D, ant_route, num_cities));

        for(j = 0; j < num_cities-1; j++)
            (ant_data->T)[ant_route[j]][ant_route[j+1]] += deposit_amount;
        (ant_data->T)[ant_route[j]][ant_route[0]] += deposit_amount; // back to start
    }

    return;
}

void evaporate_pheremones(ANT_DATA* ant_data, float evaporation_rate)
{
    int num_ants = *(ant_data->num_ants);
    int num_cities = *(ant_data->num_cities);

    int i, j;

    float** T = ant_data->T;

    // evaporate the pheremones
    for(i = 0; i < num_cities; i++)
    {
        for(j = 0; j < num_cities; j++)
        {
            // do not update unwanted pheremone values
            if(i == j) continue;
            if(T[i][j] == 0) continue;

            // float curr = T[i][j];
            T[i][j] *= (1 - evaporation_rate);
        }
    }

    return;
}

void update_pheremones(ANT_DATA* ant_data, int start_city, float Q, float evaporation_rate)
{
    int num_ants = *(ant_data->num_ants);
    int num_cities = *(ant_data->num_cities);

    // pheremone updates
    evaporate_pheremones(ant_data, evaporation_rate);
    deposit_pheremones(ant_data, Q);

    // resetting ant tabu tables for new run
    reset_ant_tabu_tables(ant_data->ant_map, num_ants, num_cities, start_city);

    return;
}

//
// ELITIST ANT SYSTEM PHEREMONE FUNCTIONS
//

void deposit_pheremones_elitist(ANT_DATA* ant_data, int* shortest, float e, float Q)
{
    // deposit pheremones like classic AS
    deposit_pheremones(ant_data, Q);

    // extra best-so-far ant deposits extra pheremone on best tour found so far
    int num_cities = *(ant_data->num_cities);
    float** T = ant_data->T;

    // computing shortest tour length heuristic for EAS
    float elitist_length_heuristic = (e / tour_length(ant_data->D, shortest, num_cities));

    int i;
    for(i = 0; i < num_cities-1; i++)
        T[shortest[i]][shortest[i+1]] += elitist_length_heuristic;
    T[shortest[i]][shortest[0]] += elitist_length_heuristic; // back to start

    return;
}

void update_pheremones_elitist(ANT_DATA* ant_data, int* shortest, int start_city, float e, float Q, float evaporation_rate)
{
    int num_ants = *(ant_data->num_ants);
    int num_cities = *(ant_data->num_cities);

    // pheremone updates
    evaporate_pheremones(ant_data, evaporation_rate);
    deposit_pheremones_elitist(ant_data, shortest, e, Q);

    // resetting ant tabu tables for new run
    reset_ant_tabu_tables(ant_data->ant_map, num_ants, num_cities, start_city);

    return;
}