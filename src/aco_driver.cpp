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
    ant_tabu_map_t mp = generate_ant_tabu_tables(num_ants, num_cities);

    // testing transition probability
    float alpha = 0.9;
    float beta = 0.5;
    // float res = transition_rule(D, pheremone_matrix, mp[0], num_cities, 2, 3, alpha, beta);
    // std::cout << "Res: " << res << std::endl;

    // testing get_next_city
    int start_city = 1;
    int* test_route = generate_ant_route(D, pheremone_matrix, mp[0], num_cities, start_city, alpha, beta);

    for(i = 0; i < num_cities; i++)
        std::cout << test_route[i] << "\t";
    
    std::cout << std::endl;

    return 0;
}