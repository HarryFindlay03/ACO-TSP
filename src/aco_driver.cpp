#include "../include/aco_driver.hpp"

// TODO: Turn common parameters passed into a struct

int main()
{
    // seeding random number generator

    // uncomment below line for prod
    // srand(time(0));

    int num_ants = 5;
    int num_cities = 14;
    int start_city = 1;
    float alpha = 0.9;
    float beta = 0.5;

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
    int** ant_routes = generate_all_ant_routes(ant_data, num_ants, num_cities, start_city, alpha, beta);

    std::cout << "TEST ANT ROUTES" << std::endl;
    for(i = 0; i < num_ants; i++)
    {
        std::cout << "ANT " << i << std::endl;
        for(j = 0; j <= num_cities; j++)
            std::cout << ant_routes[i][j] << " ";
        std::cout << std::fixed << "\t Tour Length: " << tour_length(ant_data->D, ant_routes[i], num_cities) << std::endl;
    }
    
    std::cout << std::endl;

    return 0;
}