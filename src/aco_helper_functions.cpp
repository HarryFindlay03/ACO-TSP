#include "../include/aco_helper_functions.hpp"

ANT_DATA* generate_ant_data(char* filename, int num_ants, int start_city)
{
    int num_cities = get_num_cities(filename);

    ANT_DATA* ant_data = new ANT_DATA;
    ant_data->D = generate_distance_matrix(filename, num_cities);
    ant_data->T = generate_pheremone_matrix(num_cities);
    ant_data->ant_map = generate_ant_tabu_tables(num_ants, num_cities, start_city);
    ant_data->ant_routes = generate_initial_ant_routes(num_ants, num_cities);
    ant_data->num_ants = new int(num_ants);
    ant_data->num_cities = new int(num_cities);

    return ant_data;
}

float** generate_distance_matrix(char* filename, int num_cities)
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
            float d;
            const char* s = cost.attribute("cost").value();
            sscanf(s, "%f", &d);
            distance_matrix[node_count][next_node_count] = d;
        }
    }    

    return distance_matrix;
}

float** generate_pheremone_matrix(int num_cities)
{
    // pheremone matrix will be one row longer than required to store the starting pheremones
    // a psuedo-start node is represented to allow for a actual start node in the graph to be selected.

    // ensure prng has been seeded well prior to calling this function
    float** pheremone_matrix = new float*[num_cities];

    int i, j;
    for(i = 0; i < num_cities; i++)
    {
        pheremone_matrix[i] = new float[num_cities];
        for(j = 0; j < num_cities; j++)
        {
            if(i == j)
            {
                pheremone_matrix[i][j] = 0;
                continue;
            }

            float random_number = (float)rand() / RAND_MAX;
            pheremone_matrix[i][j] = random_number;
        }
    }

    // pheremone levels for pseudostart node
    // pheremone_matrix[i] = new float[num_cities];
    // for(j = 0; j < num_cities; j++)
    // {
    //     pheremone_matrix[i][j] = (float)rand() / RAND_MAX;
    // }

    return pheremone_matrix;
}

int** generate_ant_tabu_tables(int num_ants, int num_cities, int start_city)
{
    int** mp = new int*[num_ants];
    int i, j;
    for(i = 0; i < num_ants; i++) {
        mp[i] = new int[num_cities];
        for(j = 0; j < num_cities; j++)
        {
            if(j == start_city)
            {
                mp[i][j] = 1;
                continue;
            }
            mp[i][j] = 0;
        }
    }

    return mp;
}

void reset_ant_tabu_tables(int** ant_tabu_tables, int num_ants, int num_cities, int start_city)
{
    int i, j;
    for(i = 0; i < num_ants; i++)
        for(j = 0; j < num_cities; j++)
            (start_city == j) ? ant_tabu_tables[i][j] = 1 : ant_tabu_tables[i][j] = 0;

    return;
}

int** generate_initial_ant_routes(int num_ants, int num_cities)
{
    int** ant_routes = new int*[num_ants];
    int i;
    for(i = 0; i < num_ants; i++)
        ant_routes[i] = new int[num_cities];

    return ant_routes;
}

int get_num_cities(char* filename)
{
    pugi::xml_document doc;

    // need error handling here
    if(!doc.load_file(filename))
        std::cout << "There was an error!" << std::endl;

    pugi::xml_node nodes = doc.child("travellingSalesmanProblemInstance").child("graph");

    // counting how many vertexes in the graph there are
    int node_count = 0;
    pugi::xml_node node;
    for(node = nodes.first_child(); node; node = node.next_sibling())
        node_count++;

    return node_count;
}