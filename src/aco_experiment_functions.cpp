#include "../include/aco_experiment_functions.hpp"

void run_ant_system(std::string filename, float alpha, float beta, float Q, float evaporation_rate, int num_ants, int num_cities, int iterations)
{
    // OPENING FILE
    std::ofstream results_file;
    results_file.open("results/results.txt", std::ios::app);

    // GENERATING ANT DATA
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

        generate_all_ant_routes(ant_data, s, alpha, beta, Q);

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

    std::string valid;
    (shortest_length == 3323 || shortest_length == 25395) ? valid = "✅" : valid = "❌";

    std::printf("(classic) %0f, %d/%d, %s, SHORTEST TOUR: ", shortest_length, shortest_tour_iteration, iterations, valid.c_str());

    for(i = 0; i < num_cities; i++)
        std::cout << shortest[i] << " ";
    std::cout << shortest[0] << std::endl;


    if(!tour_valid(shortest, num_cities))
    {
        std::cout << "ERROR! TOUR COMPUTED IS NOT A VALID TOUR!" << std::endl;
        std::exit(-1);
    }

    // FILE WRITING
    results_file << shortest_tour_iteration << "," << shortest_length << "," << alpha << "\n";
    results_file.close();

    delete[] shortest;
    clean_up(ant_data);

    return;
}

void run_elitist_ant_system(std::string filename, float alpha, float beta, float Q, float evaporation_rate, float e, int num_ants, int num_cities, int iterations)
{
    ANT_DATA *ant_data = generate_ant_data(filename.c_str(), num_ants, num_cities);

    int shortest_tour_position, shortest_tour_iteration;

    int i;

    // initial shortest route set
    int *shortest = new int[num_cities];
    for (i = 0; i < num_cities; i++)
        shortest[i] = i;

    int s = rand() % num_cities;

    std::cout.precision(0);
    for (i = 0; i < iterations; i++)
    {
        std::cout << std::fixed << "PROGRESS: " << ((float)i / iterations) * 100 << "%\t\r" << std::flush;

        generate_all_ant_routes(ant_data, s, alpha, beta, Q);

        // getting generation shortest tour
        shortest_tour_position = shortest_tour(ant_data->D, ant_data->ant_routes, num_ants, num_cities);
        int *generation_shortest = (ant_data->ant_routes)[shortest_tour_position];

        // using helper function that only copies over if generation shortest is shorter than global shortest
        if (copy_shortest(ant_data->D, shortest, generation_shortest, num_cities))
            shortest_tour_iteration = i;

        // setting start_city to random value in range
        s = rand() % num_cities;
        update_pheremones_elitist(ant_data, shortest, s, e, Q, evaporation_rate);
    }

    // INFORMATION OUTPUT
    float shortest_length = tour_length(ant_data->D, shortest, num_cities);

    std::string valid;
    (shortest_length == 3323 || shortest_length == 25395) ? valid = "✅" : valid = "❌";

    std::printf("(elitist) %0f, %d/%d, %s, SHORTEST TOUR: ", shortest_length, shortest_tour_iteration, iterations, valid.c_str());

    for (i = 0; i < num_cities; i++)
        std::cout << shortest[i] << " ";
    std::cout << shortest[0] << std::endl;

    if(!tour_valid(shortest, num_cities))
    {
        std::cout << "ERROR! TOUR COMPUTED IS NOT A VALID TOUR!" << std::endl;
        std::exit(-1);
    }

    delete[] shortest;
    clean_up(ant_data);

    return;
}