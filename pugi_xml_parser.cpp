#include <iostream>
#include "pugixml.hpp"

float** get_distance_matrix(char*, int);

int main()
{
    int num_cities = 14;

    char* filename = new char[sizeof("burma14.xml")];
    strcpy(filename, "burma14.xml");

    float** distance_matrix = get_distance_matrix(filename, num_cities);

    int i, j;
    for (i = 0; i < num_cities; i++)
    {
        for (j = 0; j < num_cities; j++)
        {
            std::cout << std::fixed;
            std::cout.precision(0);
            std::cout << distance_matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    return 0;
}

float** get_distance_matrix(char* filename, int num_cities)
{
    pugi::xml_document doc;
    // need error handling here
    doc.load_file(filename);

    pugi::xml_node nodes = doc.child("travellingSalesmanProblemInstance").child("graph");

    int node_count, next_node_count;
    pugi::xml_node node, cost;

    float** distance_matrix = new float*[num_cities];

    for(node = nodes.first_child(), node_count = 0; node; node_count++, node = node.next_sibling())
    {
        distance_matrix[node_count] = new float[num_cities]; 
        for(cost = node.first_child(), next_node_count = 0; cost; cost = cost.next_sibling(), next_node_count++)
        {
            //ignores itself
            if(node_count == next_node_count) next_node_count++;


            // converting to a double
            double d;
            const char* s = cost.attribute("cost").value();
            sscanf(s, "%lf", &d);
            distance_matrix[node_count][next_node_count] = d;
        }
    }

    return distance_matrix;
}



