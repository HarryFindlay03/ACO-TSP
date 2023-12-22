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

    std::string tour_opt;
    (shortest_length == 3323 || shortest_length == 25395) ? tour_opt = "TRUE" : tour_opt = "FALSE";

    // INFORMATION OUTPUT
    std::printf("TOUR LENGTH: %.0f\n", shortest_length);
    std::printf("TOUR OPTIMUM: %s\n", tour_opt.c_str());
    std::printf("FOUND AT ITERATION: %d\n", shortest_tour_iteration);
    std::printf("TOTAL ITERATIONS: %d\n", iterations);
    std::printf("TOUR FOUND: ");

    for(i = 0; i < num_cities; i++)
        std::cout << shortest[i] << " ";
    std::cout << shortest[0] << std::endl;

    // EXIT THE PROGRAM IS TOUR FOUND IS NOT VALID
    if(!tour_valid(shortest, num_cities))
    {
        std::cout << "ERROR! TOUR COMPUTED IS NOT A VALID TOUR! EXITING THE PROGRAM..." << std::endl;
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

    std::string tour_opt;
    (shortest_length == 3323 || shortest_length == 25395) ? tour_opt = "TRUE" : tour_opt = "FALSE";

    // INFORMATION OUTPUT
    std::printf("TOUR LENGTH: %.0f\n", shortest_length);
    std::printf("TOUR OPTIMUM: %s\n", tour_opt.c_str());
    std::printf("FOUND AT ITERATION: %d\n", shortest_tour_iteration);
    std::printf("TOTAL ITERATIONS: %d\n", iterations);
    std::printf("TOUR FOUND: ");

    for(i = 0; i < num_cities; i++)
        std::cout << shortest[i] << " ";
    std::cout << shortest[0] << std::endl;

    // EXIT THE PROGRAM IS TOUR FOUND IS NOT VALID
    if(!tour_valid(shortest, num_cities))
    {
        std::cout << "ERROR! TOUR COMPUTED IS NOT A VALID TOUR! EXITING THE PROGRAM..." << std::endl;
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

void run_with_param_logging(std::string& filename, float alpha, float beta, float Q, float evaporation_rate, int num_ants, int num_cities, int iterations, std::string file_extra)
{
    // RUN ON ALL PARAMETERS if no file_extra given - by calling the function with all the parameters.
    if(file_extra == "0")
    {
        const char* v[] = {"alpha", "beta", "evap", "Q"}; 
        std::vector<std::string> params(v, v + 4);

        std::vector<std::string>::iterator it;
        for(it = params.begin(); it != params.end(); ++it)
            run_with_param_logging(filename, alpha, beta, Q, evaporation_rate, num_ants, num_cities, iterations, *it);

        return;
    }

    // OPENING RESULTS FILE
    std::ofstream results_file;
    std::string file_iden("results/results_");
    file_iden += file_extra + ".txt";

    results_file.open(file_iden);
    results_file << "iteration,length,param\n";
    results_file.close();

    // change loop bounds depending on file
    float start, end, step;
    if(file_extra == "alpha") {start = 0.5; end = 1.5; step = 0.1;}
    else if(file_extra == "beta") {start = 1; end = 11; step = 1;}
    else if(file_extra == "evap") {start = 0.1; end = 1.1; step = 0.1;}
    else if(file_extra == "Q") {start = 1; end = 11; step = 1;}
    else if(file_extra == "numants") {start = 101; end = 152; step = 10;}
    else {start = 0; end = 1; step = 1;} //run it once


    // RUN ANT SYSTEM
    int retries = 3;
    int i;
    float param;
    for(param = start; param < end; param += step)
    {
        if(file_extra == "alpha") alpha = param;
        else if(file_extra == "beta") beta = param;
        else if(file_extra == "evap") evaporation_rate = param;
        else if(file_extra == "Q") Q = param;
        else if(file_extra == "numants") num_ants = param;

        for (i = 0; i < retries; i++)
        {
            run_ant_system(filename, alpha, beta, Q, evaporation_rate, num_ants, num_cities, iterations, file_extra, 0, 0);
            // run_ant_system_elitist(filename, alpha, beta, Q, evaporation_rate, num_cities, num_ants, num_cities, iterations, file_extra);
            // parameter ouptut
            std::printf("alpha=%.1f, beta=%.0f, Q=%.0f, evaporation rate=%.1f, num_ants=%d\n", alpha, beta, Q, evaporation_rate, num_ants);
        }
    }

    return; 
}

void run_with_per_iteration_logging(std::string& filename, float alpha, float beta, float Q, float evaporation_rate, int num_ants, int num_cities, int iterations, int approach_type, std::string output_ext)
{
    // OPENING RESULTS FILE
    std::ofstream results_file;
    std::string file_iden("results/results_");
    file_iden += output_ext + ".txt";

    results_file.open(file_iden);
    results_file << "lengthOptimaSoFar,iteration\n";
    results_file.close();

    // RUN ANT SYSTEM
    int retries = 5;
    int i;
    float param;
    for (i = 0; i < retries; i++)
    {
        if(approach_type == 1)
            run_ant_system(filename, alpha, beta, Q, evaporation_rate, num_ants, num_cities, iterations, output_ext, 0, 1);
        else
            run_ant_system_elitist(filename, alpha, beta, Q, evaporation_rate, num_cities, num_ants, num_cities, iterations, output_ext, 1, 1);

        // parameter ouptut
        std::printf("alpha=%.1f, beta=%.0f, Q=%.0f, evaporation rate=%.1f\n", alpha, beta, Q, evaporation_rate);
    }

    return;
}