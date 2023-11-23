#include "../include/aco_functions.hpp"

float city_pair_distance_heuristic(float** D, int x, int y) { return 1 / D[x][y]; }

float transition_rule(float** D, float** T, int* ant_tabu_table, int num_cities, int city_i, int city_j, float alpha, float beta)
{
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



