#include "../include/aco_driver.hpp"

// TODO
// TODO - adding num ants and num cities into ant data structure

int main()
{
    // seeding random number generator

    // uncomment below line for prod
    // srand(time(0));

    // PARAMETERS
    int num_ants = 5;
    int num_cities = 14;
    int start_city = 1;
    float alpha = 0.9;
    float beta = 0.5;
    float Q = 2;
    float evaporation_rate = 0.2;

    char* filename = new char[sizeof("data/burma14.xml")];
    strcpy(filename, "data/burma14.xml");

    int i, j;

    ANT_DATA* ant_data = generate_ant_data(filename, num_ants, num_cities, start_city);

    // generating distance matrix 
    float** D = ant_data->D;
    for (i = 0; i < num_cities; i++)
    {
        for (j = 0; j < num_cities; j++)
        {
            std::cout << D[i][j] << "\t";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl << std::endl;

    // generating initial random pheremone matrix
    float** pheremone_matrix = ant_data->T; 
    for (i = 0; i < num_cities; i++)
    {
        for (j = 0; j < num_cities; j++)
        {
            std::cout.precision(2);
            std::cout << pheremone_matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl << std::endl;

    // testing generating ant routes
    int x;
    for(x = 0; x < 10000; x++)
    {
        generate_all_ant_routes(ant_data, num_ants, num_cities, start_city, alpha, beta);

        std::cout << "TEST ANT ROUTES: " << x << std::endl;
        std::cout << std::fixed;
        for (i = 0; i < num_ants; i++)
        {
            int *ant_route = (ant_data->ant_routes)[i];
            std::cout << "ANT " << i << std::endl;
            for (j = 0; j <= num_cities; j++)
                std::cout << ant_route[j] << " ";
            std::cout << "\t Tour Length: " << tour_length(ant_data->D, ant_route, num_cities) << std::endl;
        }

        prepare_new_run(ant_data, num_ants, num_cities, start_city, Q, evaporation_rate);

        std::cout << std::endl << std::endl;
    }


    return 0;
}