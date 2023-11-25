#include "../include/aco_driver.hpp"

// TODO: Turn common parameters passed into a struct

int main()
{
    // seeding random number generator

    // uncomment below line for prod
    // srand(time(0));

    int num_cities = 14;

    char* filename = new char[sizeof("data/burma14.xml")];
    strcpy(filename, "data/burma14.xml");

    int i, j;

    // generating distance matrix 
    float** D = generate_distance_matrix(filename, num_cities);
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
    float** pheremone_matrix = generate_pheremone_matrix(num_cities);
    for (i = 0; i < num_cities; i++)
    {
        for (j = 0; j < num_cities; j++)
        {
            std::cout.precision(2);
            std::cout << pheremone_matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }

    // getting ant tabu table
    std::cout << std::endl << std::endl;

    int num_ants = 5;
    int start_city = 1;
    ant_tabu_map_t mp = generate_ant_tabu_tables(num_ants, num_cities, start_city);

    // testing transition probability
    float alpha = 0.9;
    float beta = 0.5;
    // float res = transition_rule(D, pheremone_matrix, mp[0], num_cities, 2, 3, alpha, beta);
    // std::cout << "Res: " << res << std::endl;

    // testing get_next_city

    // testing generating ant routes
    int** ant_routes = generate_all_ant_routes(D, pheremone_matrix, mp, num_ants, num_cities, start_city, alpha, beta);

    std::cout << "TEST ANT ROUTES" << std::endl;
    for(i = 0; i < num_ants; i++)
    {
        std::cout << "ANT " << i << std::endl;
        for(j = 0; j < num_cities; j++)
            std::cout << ant_routes[i][j] << " ";
        std::cout << std::endl;
    }
    
    std::cout << std::endl;

    return 0;
}