#include "../include/aco_functions.hpp"

float city_pair_distance_heuristic(float** D, int x, int y) { return 1 / D[x][y]; }

int* generate_ant_route(float** D, float** T, int* ant_tabu_table, int num_cities, int start_city, float alpha, float beta)
{
    int* ant_route = new int[num_cities];
    ant_route[0] = start_city;

    int i = 1;
    while(i < num_cities)
    {
        int next = get_next_city(D, T, ant_tabu_table, num_cities, ant_route[i-1], alpha, beta);
        ant_route[i] = next;
        ant_tabu_table[next] = 1;
        i++;
    }

    return ant_route;
}

int get_next_city(float** D, float** T, int* ant_tabu_table, int num_cities, int start_city, float alpha, float beta)
{
    int i;
    float probs[num_cities];

    for(i = 0; i < num_cities; i++)
        probs[i] = transition_rule(D, T, ant_tabu_table, num_cities, start_city, i, alpha, beta);

    // remaining cities to work out cumulative prob and return correct city
    std::vector<int> remaining_cities;
    for(i = 0; i < num_cities; i++)
        if(probs[i])
            remaining_cities.push_back(i);

    int pos = 0;
    float cumulative_probs[remaining_cities.size()];
    float res = 0;
    for (i = 0; i < num_cities; i++)
    {
        if(probs[i])
        {
            res += probs[i];
            cumulative_probs[pos++] = res;
        }
    }

    // return which city to visit next 
    float spin = (float)rand() / RAND_MAX;
    i = 0;
    while (cumulative_probs[i] < spin)
        i++;

    return remaining_cities[i];
}

float transition_rule(float** D, float** T, int* ant_tabu_table, int num_cities, int city_i, int city_j, float alpha, float beta)
{
    if(city_i == city_j) return 0;
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
            if(city_i == h) continue; // skips the pheremone strength and distance between city_i and itself (testing phase this will be taken out later)
            dom += (std::pow(T[city_i][h], alpha) * std::pow(city_pair_distance_heuristic(D, city_i, h), beta));
        }
    }

    return (nom / dom);
}



