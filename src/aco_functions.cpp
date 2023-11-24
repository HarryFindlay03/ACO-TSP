#include "../include/aco_functions.hpp"

float city_pair_distance_heuristic(float** D, int x, int y) { return 1 / D[x][y]; }

int get_next_city(float** D, float** T, int* ant_tabu_table, int num_ants, int num_cities, int start_city, float alpha, float beta)
{
    int i;
    float probs[num_cities];

    // generate cumulative probabilites of which city to visit next
    for (i = 1; i < num_cities; i++)
    {
        if (start_city == i) continue; 
        if (i == 0)
        {
            probs[i] = transition_rule(D, T, ant_tabu_table, num_cities, start_city, i, alpha, beta);
            continue;
        }
        probs[i] = probs[i - 1] + transition_rule(D, T, ant_tabu_table, num_cities, start_city, i, alpha, beta);
    }

    // choose which city to visit next
    float spin = (float)rand() / RAND_MAX;
    i = 0;
    while(probs[i] < spin)
        i++;
    
    return i;
}

float transition_rule(float** D, float** T, int* ant_tabu_table, int num_cities, int city_i, int city_j, float alpha, float beta)
{
    if(city_i == city_j) return 0;

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



