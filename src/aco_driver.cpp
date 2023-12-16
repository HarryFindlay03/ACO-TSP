#include "../include/aco_driver.hpp"

// TSPLIB ANSWERS
// BURMA14: 3323
// BRAZIL58: 25395

int main()
{
    // seeding random number generator - uncomment below for prod
    // srand(time(0));

    // INITIAL PARAMETERS
    float alpha = 1; // alpha > 1 leads to stagnation
    float beta = 9; // Lower beta for lower amount of cities
    float Q = 1; // ACO BOOK SAYS Q = 1
    float evaporation_rate = 0.5;

    // ENTER PATH OF FILENAME HERE - FROM ROOT
    // std::string filename("data/burma14.xml");
    std::string filename("data/brazil58.xml");
    std::cout << std::endl << "FILENAME: " << filename << std::endl << std::endl;

    int num_cities = get_num_cities(filename.c_str());
    int num_ants = 50;

    std::cout << "NUMBER OF CITIES: " << num_cities << std::endl;
    std::cout << "NUMBER OF ANTS: " << num_ants << std::endl << std::endl;

    // RUN ANT SYSTEM
    int iterations = 1000;
    int retries = 1;
    int i;
    for(i = 0; i < retries; i++)
    {
        run_ant_system(filename, alpha, beta, Q, evaporation_rate, num_ants, num_cities, iterations);
        run_elitist_ant_system(filename, alpha, beta, evaporation_rate, num_ants, num_cities, iterations);
    }

    return 0;
}