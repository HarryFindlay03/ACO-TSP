#include "../include/aco_driver.hpp"

// TODO
// Look at generating initial tabu tables without start city - fill them only when running 

// TSPLIB ANSWERS
// BURMA14: 3323
// BRAZIL58: 25395

int main()
{
    // seeding random number generator - uncomment below for prod
    // srand(time(0));

    // PARAMETERS
    int num_ants = 10;
    float alpha = 0.9;
    float beta = 0.5;
    float Q = 5;
    float evaporation_rate = 0.3;

    // reading filename
    char* filename = new char[sizeof("data/burma14.xml")];
    strcpy(filename, "data/burma14.xml");

    // generating initial ant data
    ANT_DATA* ant_data = generate_ant_data(filename, num_ants);
    int num_cities = *(ant_data->num_cities);

    std::cout << "NUM CITIES " << num_cities << std::endl;

    // distance matrix
    const matrix_t& D = ant_data->D;

    // pheremone matrix
    float** pheremone_matrix = ant_data->T; 

    int i, j;
    // generating placeholder route
    int* shortest = new int[num_cities];
    for(i = 0; i < num_cities; i++)
        shortest[i] = i;

    // testing generating ant routes
    int x, s, shortest_tour_pos;
    int shortest_route_iteration = 0;

    for(s = 0; s < num_cities; s++)
    {
        for (x = 0; x < 1000; x++)
        {

            generate_all_ant_routes(ant_data, s, alpha, beta);

            // getting shortest tour
            shortest_tour_pos = shortest_tour(D, ant_data->ant_routes, num_ants, num_cities);
            if (tour_length(D, (ant_data->ant_routes)[shortest_tour_pos], num_cities) < tour_length(D, shortest, num_cities))
            {
                // copy into shortest the ant route in ant_routes
                for (j = 0; j < num_cities; j++)
                    shortest[j] = (ant_data->ant_routes)[shortest_tour_pos][j];
                shortest_route_iteration = x;
            }

            prepare_new_run(ant_data, s, Q, evaporation_rate);
        }
    }

    std::cout << std::fixed;
    std::cout << "SHORTEST ROUTE FOUND: ";
    for(i = 0; i < num_cities; i++)
        std::cout << shortest[i] << " ";
    std::cout << shortest[0] << "\nTOUR LENGTH: " << tour_length(D, shortest, num_cities) << "\tITERATION: " << shortest_route_iteration << std::endl;

    return 0;
}


// for (i = 0; i < num_cities; i++)
// {
//     for (j = 0; j < num_cities; j++)
//     {
//         std::cout << D[i][j] << "\t";
//     }
//     std::cout << std::endl;
// }

// std::cout << std::endl << std::endl;
// for (i = 0; i < num_cities; i++)
// {
//     for (j = 0; j < num_cities; j++)
//     {
//         std::cout.precision(2);
//         std::cout << pheremone_matrix[i][j] << "\t";
//     }
//     std::cout << std::endl;
// }

// std::cout << std::endl << std::endl;