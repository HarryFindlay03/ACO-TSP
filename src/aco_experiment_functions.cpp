#include "../include/aco_experiment_functions.hpp"

void run_ant_system(std::string& filename, float alpha, float beta, float Q, float evaporation_rate, int num_ants, int num_cities, int iterations, std::string file_extra, int use_heuristic, int iteration_logging)
{
    // GENERATING ANT DATA
    ANT_DATA* ant_data = generate_ant_data(filename.c_str(), num_ants, num_cities, use_heuristic);

    // OPENING ITERATION LOGGING FILE
    std::ofstream results_iteration_logging;
    if (iteration_logging)
    {
        std::string file_iteration_logging_iden = "results/results_" + file_extra + ".txt";
        results_iteration_logging.open(file_iteration_logging_iden, std::ios::app);
    }

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

        // ITERATION LOGGING FILE WRITING
        if (iteration_logging)
        {
            results_iteration_logging << tour_length(ant_data->D, generation_shortest, num_cities) << "," << i << "\n";
        }

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
    if(!(file_extra == "0") && !(iteration_logging))
    {
        std::string file_iden = "results/results_" + file_extra + ".txt";
        std::ofstream results_file;
        results_file.open(file_iden, std::ios::app);

        float param;
        if(file_extra == "alpha") param = alpha;
        else if(file_extra == "beta") param = beta;
        else if(file_extra == "evap") param = evaporation_rate;
        else if(file_extra == "Q") param = Q;
        else param = num_ants;

        results_file << shortest_tour_iteration << "," << shortest_length << "," << param << "\n";
        results_file.close();
    }

    if(iteration_logging) results_iteration_logging.close();

    delete[] shortest;
    clean_up(ant_data);

    return;
}

void run_ant_system_elitist(std::string& filename, float alpha, float beta, float Q, float evaporation_rate, float e, int num_ants, int num_cities, int iterations, std::string file_extra, int use_heuristic, int iteration_logging)
{
    // GENERATING ANT DATA
    ANT_DATA* ant_data = generate_ant_data(filename.c_str(), num_ants, num_cities, use_heuristic);

    // OPENING ITERATION LOGGING FILE
    std::ofstream results_iteration_logging;
    if (iteration_logging)
    {
        std::string file_iteration_logging_iden = "results/results_" + file_extra + ".txt";
        results_iteration_logging.open(file_iteration_logging_iden, std::ios::app);
    }

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

        // ITERATION LOGGING FILE WRITING
        if (iteration_logging)
        {
            results_iteration_logging << tour_length(ant_data->D, generation_shortest, num_cities) << "," << i << "\n";
        }

        // setting start_city to random value in range
        s = rand() % num_cities;
        update_pheremones_elitist(ant_data, shortest, s, e, Q, evaporation_rate);
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
    if(!(file_extra == "0") && !(iteration_logging))
    {
        std::string file_iden = "results/results_" + file_extra + ".txt";
        std::ofstream results_file;
        results_file.open(file_iden, std::ios::app);

        float param;
        if(file_extra == "alpha") param = alpha;
        else if(file_extra == "beta") param = beta;
        else if(file_extra == "evap") param = evaporation_rate;
        else param = Q;

        results_file << shortest_tour_iteration << "," << shortest_length << "," << param << "\n";
        results_file.close();
    }

    if(iteration_logging) results_iteration_logging.close();

    delete[] shortest;
    clean_up(ant_data);

    return;
}