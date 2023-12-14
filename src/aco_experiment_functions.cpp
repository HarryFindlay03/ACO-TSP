#include "../include/aco_experiment_functions.hpp"

void run_ant_system(std::string filename, float alpha, float beta, float Q, float evaporation_rate, int num_ants, int num_cities, int iterations)
{
    ANT_DATA* ant_data = generate_ant_data(filename.c_str(), num_ants, num_cities);

    int shortest_tour_position, shortest_tour_iteration;

    int i;

    // initial shortest route set
    int* shortest = new int[num_cities];
    for(i = 0; i < num_cities; i++)
        shortest[i] = i;

    int s = rand() % num_cities;

    std::cout.precision(0);
    for (i = 0; i < iterations; i++)
    {
        std::cout << std::fixed << "PROGRESS: " << ((float)i / iterations) * 100 << "%\t\r" << std::flush;

        generate_all_ant_routes(ant_data, s, alpha, beta);

        // getting generation shortest tour
        shortest_tour_position = shortest_tour(ant_data->D, ant_data->ant_routes, num_ants, num_cities);
        int *generation_shortest = (ant_data->ant_routes)[shortest_tour_position];

        // using helper function that only copies over if generation shortest is shorter than global shortest
        if (copy_shortest(ant_data->D, shortest, generation_shortest, num_cities))
            shortest_tour_iteration = i;

        // setting start_city to random value in range
        s = rand() % num_cities;
        update_pheremones(ant_data, s, Q, evaporation_rate);
    }

    // INFORMATION OUTPUT
    float shortest_length = tour_length(ant_data->D, shortest, num_cities);
    std::printf("%0f, %d/%d, SHORTEST TOUR: ", shortest_length, shortest_tour_iteration, iterations);
    
    for(i = 0; i < num_cities; i++)
        std::cout << shortest[i] << " ";
    std::cout << shortest[0] << std::endl;

    delete[] shortest;
    clean_up(ant_data);

    return;
}