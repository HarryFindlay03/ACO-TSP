#include "../include/aco_driver.hpp"

// TSPLIB ANSWERS
// BURMA14: 3323
// BRAZIL58: 25395

int main(int argc, char* argv[])
{
    std::cout << std::endl;

    std::string filename;
    std::string param_filename;
    int params_provided = 0;
    // GETTING CLI INPUT <filename>
    if(argc == 1)
    {
        // no filename provided
        std::cout << "NO INPUT ARGUMENTS PROVIDED!" << std::endl;

        std::cout << "PLEASE ENTER FILENAME (path to from root): ";
        std::cin >> filename;
    }
    if(argc > 1) //filename has been provided
    {
        filename = argv[1];

        // filename error handling
        is_valid_xml_filename(filename);
    }
    if(argc > 2) //param filename has been provided
    {
        param_filename = argv[2];

        // parameter filename erorr checking
        if(is_valid_param_filename(param_filename))
            params_provided = 1;
    }

    // DEFAULT INITIAL PARAMETERS IF PARAM_FILE NOT PROVIDED
    float alpha = 1; // alpha > 1 leads to stagnation
    float beta = 4; // Lower beta for lower amount of cities
    float Q = 1; // ACO BOOK SAYS Q = 1
    float evaporation_rate = 0.5;
    int num_ants;
    int iterations = 10000;
    int use_heuristic = 1;
    int approach_type = 0;
    int retries = 1;

    // read the param_filename if it has been provided
    if(params_provided)
    {
        float* params = new float[9];
        if(get_params(param_filename, params))
        {
            num_ants = (int)params[0];
            alpha = params[1];
            beta = params[2];
            Q = params[3];
            evaporation_rate = params[4];
            iterations = (int)params[5];
            use_heuristic = (int)params[6];
            approach_type = (int)params[7];
            retries = (int)params[8];
        }
        delete[] params;
    }

    // seeding random number generator - uncomment below for prod
    srand(time(0));

    std::cout << std::endl << "FILENAME: " << filename << std::endl;
    std::string output_param_filename;
    params_provided ? output_param_filename = param_filename : output_param_filename = "default";
    std::cout << "PARAMETER FILENAME: " << output_param_filename << std::endl << std::endl;

    int num_cities = get_num_cities(filename.c_str());
    if(!params_provided)
        num_ants = num_cities;
    float e = num_cities; // ACO book says this is a good level of reinforcement for Tbs.

    std::cout << "PARAMETERS" << std::endl;
    std::cout << "NUMBER OF CITIES: " << num_cities << std::endl;
    std::cout << "NUMBER OF ANTS: " << num_ants << std::endl;
    std::cout << "ALPHA: " << alpha << std::endl;
    std::cout << "BETA: " << beta << std::endl;
    std::cout << "Q: " << Q << std::endl;
    std::cout << "EVAPORATION RATE: " << evaporation_rate << std::endl;

    std::string h;
    use_heuristic ? h = "TRUE" : h = "FALSE";
    std::cout << "USE T0 HEURISTIC: " << h << std::endl;
    approach_type ? h = "ELITIST" : h = "CLASSIC";
    std::cout << "APPROACH: " << h << std::endl;
    std::cout << "RUNS: " << retries << std::endl;

    std::cout << std::endl;

    // RUNNING THE ANT SYSTEM
    int i;
    for(i = 0; i < retries; i++)
    {
        std::cout << "RUN " << (i+1) << std::endl;
        if (approach_type == 0)
        {
            run_ant_system(filename, alpha, beta, Q, evaporation_rate, num_ants, num_cities, iterations, "0", use_heuristic, 0);
        }
        else
        {
            run_ant_system_elitist(filename, alpha, beta, Q, evaporation_rate, e, num_ants, num_cities, iterations, "0", use_heuristic, 0);
        }
        std::cout << "\n\n";
    }

    // LOGGING FUNCTIONALITY
    // std::string file_extra("numants"); // change this to change results
    // run_with_param_logging(filename, alpha, beta, Q, evaporation_rate, num_ants, num_cities, iterations, file_extra);
    // run_with_per_iteration_logging(filename, alpha, beta, Q, evaporation_rate, num_ants, num_cities, iterations, 1, file_extra);

    return 0;
}