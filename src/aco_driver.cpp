#include "../include/aco_driver.hpp"

int main()
{
    int num_cities = 14;

    char* filename = new char[sizeof("data/burma14.xml")];
    strcpy(filename, "data/burma14.xml");

    float** distance_matrix = get_distance_matrix(filename, num_cities);

    int i, j;
    for (i = 0; i < num_cities; i++)
    {
        for (j = 0; j < num_cities; j++)
        {
            std::cout << distance_matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    return 0;
}