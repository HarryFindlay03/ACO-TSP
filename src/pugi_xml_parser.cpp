#include "../include/pugi_xml_parser.hpp"

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

float** get_distance_matrix(char* filename, int num_cities)
{
    pugi::xml_document doc;
    // need error handling here
    if(!doc.load_file(filename))
        std::cout << "There was an error!" << std::endl;

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



