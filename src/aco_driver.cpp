#include "../include/aco_driver.hpp"

// TSPLIB ANSWERS
// BURMA14: 3323
// BRAZIL58: 25395

int main()
{
    // seeding random number generator - uncomment below for prod
    srand(time(0));

    // INITIAL PARAMETERS
    float alpha = 1; // alpha > 1 leads to stagnation
    float beta = 4; // Lower beta for lower amount of cities
    float Q = 1; // ACO BOOK SAYS Q = 1
    float evaporation_rate = 0.5;

    // ENTER PATH OF FILENAME HERE - FROM ROOT
    // std::string filename("data/burma14.xml");
    std::string filename("data/brazil58.xml");
    std::cout << std::endl << "FILENAME: " << filename << std::endl << std::endl;

    int num_cities = get_num_cities(filename.c_str());
    int num_ants = 14;

    float e = num_cities; // ACO book says this is a good level of reinforcement for Tbs.

    std::cout << "NUMBER OF CITIES: " << num_cities << std::endl;
    std::cout << "NUMBER OF ANTS: " << num_ants << std::endl << std::endl;

    int iterations = 1000;

    std::string file_extra("numants_brazil"); // change this to change results
    run_with_logging(filename, alpha, beta, Q, evaporation_rate, num_ants, num_cities, iterations, file_extra);
    // run_with_per_iteration_logging(filename, alpha, beta, Q, evaporation_rate, num_ants, num_cities, iterations, 1);

    return 0;
}

void run_with_logging(std::string& filename, float alpha, float beta, float Q, float evaporation_rate, int num_ants, int num_cities, int iterations, std::string file_extra)
{
    // RUN ON ALL PARAMETERS if no file_extra given - by calling the function with all the parameters.
    if(file_extra == "0")
    {
        const char* v[] = {"alpha", "beta", "evap", "Q"}; 
        std::vector<std::string> params(v, v + 4);

        std::vector<std::string>::iterator it;
        for(it = params.begin(); it != params.end(); ++it)
            run_with_logging(filename, alpha, beta, Q, evaporation_rate, num_ants, num_cities, iterations, *it);

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
    else {start = 1; end = 102; step = 10;}


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
        else num_ants = param;

        for (i = 0; i < retries; i++)
        {
            run_ant_system(filename, alpha, beta, Q, evaporation_rate, num_ants, num_cities, iterations, file_extra, 0);
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
    int retries = 15;
    int i;
    float param;
    for (i = 0; i < retries; i++)
    {
        run_ant_system(filename, alpha, beta, Q, evaporation_rate, num_ants, num_cities, iterations, output_ext, 0, 1);
        // run_ant_system_elitist(filename, alpha, beta, Q, evaporation_rate, num_cities, num_ants, num_cities, iterations, output_ext, 1, 1);
        // parameter ouptut
        std::printf("alpha=%.1f, beta=%.0f, Q=%.0f, evaporation rate=%.1f\n", alpha, beta, Q, evaporation_rate);
    }

    return;
}