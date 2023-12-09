#include "../include/aco_driver.hpp"

// TODO
// TODO - Getting it to start from points that have a pheremone on them

// TSPLIB ANSWERS
// BURMA14: 3323
// BRAZIL58: 25395

int main()
{
    // seeding random number generator

    // uncomment below line for prod
    // srand(time(0));

    // PARAMETERS
    int num_ants = 10;
    int start_city = 0;
    float alpha = 0.9;
    float beta = 0.5;
    float Q = 5;
    float evaporation_rate = 0.3;

    char* filename = new char[sizeof("data/burma14.xml")];
    strcpy(filename, "data/burma14.xml");

    int i, j;

    ANT_DATA* ant_data = generate_ant_data(filename, num_ants, start_city);
    int num_cities = *(ant_data->num_cities);

    std::cout << "NUM CITIES " << num_cities << std::endl;

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

    // generating placeholder route
    int* shortest = new int[num_cities];
    for(i = 0; i < num_cities; i++)
        shortest[i] = i;

    // testing generating ant routes
    int x, s, shortest_tour_pos;
    int shortest_route_iteration = 0;

    for (x = 0; x < 10000; x++)
    {

        generate_all_ant_routes(ant_data, start_city, alpha, beta);

        // getting shortest tour
        shortest_tour_pos = shortest_tour(D, ant_data->ant_routes, num_ants, num_cities);
        if (tour_length(D, (ant_data->ant_routes)[shortest_tour_pos], num_cities) < tour_length(D, shortest, num_cities))
        {
            // copy into shortest the ant route in ant_routes
            for (j = 0; j < num_cities; j++)
                shortest[j] = (ant_data->ant_routes)[shortest_tour_pos][j];
            shortest_route_iteration = x;
        }

        prepare_new_run(ant_data, start_city, Q, evaporation_rate);
    }

    std::cout << std::fixed;
    std::cout << "SHORTEST ROUTE FOUND: ";
    for(i = 0; i < num_cities; i++)
        std::cout << shortest[i] << " ";
    std::cout << shortest[0] << "\nTOUR LENGTH: " << tour_length(D, shortest, num_cities) << "\tITERATION: " << shortest_route_iteration << std::endl;

    // std::cout << "TEST ANT ROUTES: " << x << std::endl;
    // std::cout << std::fixed;
    // for (i = 0; i < num_ants; i++)
    // {
    //     int *ant_route = (ant_data->ant_routes)[i];
    //     std::cout << "ANT " << i << std::endl;
    //     for (j = 0; j <= num_cities; j++)
    //         std::cout << ant_route[j] << " ";
    //     std::cout << "\t Tour Length: " << tour_length(ant_data->D, ant_route, num_cities) << std::endl;
    // }

    return 0;
}