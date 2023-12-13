#include "../include/aco_helper_functions.hpp"

// TODO
// reset ant tabu tables before generating ant routes !

ANT_DATA* generate_ant_data(const char* filename, int num_ants)
{
    int num_cities = get_num_cities(filename);

    ANT_DATA* ant_data = new ANT_DATA;
    ant_data->D = generate_distance_matrix(filename, num_cities);
    ant_data->T = generate_pheremone_matrix(ant_data->D, num_cities);
    ant_data->ant_map = generate_ant_tabu_tables(num_ants, num_cities);
    ant_data->ant_routes = generate_initial_ant_routes(num_ants, num_cities);
    ant_data->num_ants = new int(num_ants);
    ant_data->num_cities = new int(num_cities);

    return ant_data;
}

float** generate_distance_matrix(const char* filename, int num_cities)
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
            if(node_count == next_node_count)
                distance_matrix[node_count][next_node_count++] = 0;
                
            // converting to a double
            const char* s = cost.attribute("cost").value();
            distance_matrix[node_count][next_node_count] = std::stof(s);
        }
    }    

    return distance_matrix;
}

float** generate_pheremone_matrix(float** D, int num_cities)
{
    // ensure prng has been seeded well prior to calling this function
    float** pheremone_matrix = new float*[num_cities];

    // nearest neighbour tour heuristic value
    float nn_tour_heurisitc = (1 / shortest_nn_tour(D, num_cities));

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

            // USING NEAREST NEIGHBOUR HEURISTIC TO SET INITIAL PHEREMONE LEVEL
            // DORIGO, SUTZE, Ant Colonty Optimization
            pheremone_matrix[i][j] = nn_tour_heurisitc;
        }
    }

    return pheremone_matrix;
}

int** generate_ant_tabu_tables(int num_ants, int num_cities)
{
    int** mp = new int*[num_ants];
    int i, j;
    for(i = 0; i < num_ants; i++)
    {
        mp[i] = new int[num_cities];
        for(j = 0; j < num_cities; j++)
        {
            mp[i][j] = 0;
        }
    }

    return mp;
}

void reset_ant_tabu_tables(int** ant_tabu_tables, int num_ants, int num_cities, int start_city)
{
    int i, j;
    for(i = 0; i < num_ants; i++)
    {
        for (j = 0; j < num_cities; j++)
        {
            if(start_city == j)
                ant_tabu_tables[i][j] = 1;
            else
                ant_tabu_tables[i][j] = 0;
        }
    }

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

int get_num_cities(const char* filename)
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

// BELOW CODE IS FOR NEAREST NEIGHBOUR HEURISTIC
float nearest_neighbour_tour_length(float** D, int num_cities, int start_city)
{
    int* nn_tour = new int[num_cities];
    int* visited = new int[num_cities];

    nn_tour[0] = start_city;
    visited[start_city] = 1;

    int i, next;
    for(i = 1; i < num_cities; i++)
    {
        next = nearest_neighbour_get_next_city(D, visited, num_cities, nn_tour[i-1]);
        nn_tour[i] = next;
        visited[next] = 1; 
    }

    delete[] visited;

    // get tour length
    float res = nn_tour_length(D, nn_tour, num_cities);

    delete[] nn_tour;

    return res;
}

int nearest_neighbour_get_next_city(float** D, int* visited, int num_cities, int curr_city)
{
    // get row of tour pos
    float* curr_row = D[curr_city];

    // set shortest to the first unvisited node
    int i, shortest;
    for(i = 0; i < num_cities; i++)
    {
        if(!visited[i])
        {
            shortest = i;
            break;
        }
    }

    // go from shortest onwards
    for(i = shortest; i < num_cities; i++)
    {
        if((!visited[i]) && (curr_row[i] != 0) && (curr_row[i] < curr_row[shortest]))
            shortest = i;
    }

    return shortest;
}

float shortest_nn_tour(float** D, int num_cities)
{
    float shortest = nearest_neighbour_tour_length(D, num_cities, 0);

    float curr;
    int i;
    for(i = 1; i < num_cities; i++)
    {
        curr = nearest_neighbour_tour_length(D, num_cities, i);
        if(curr < shortest)
        {
            shortest = curr;
        }
    }

    return shortest;
}

float nn_tour_length(float** D, int* tour, int num_cities)
{
    float res = 0;

    int i;
    for(i = 0; i < num_cities-1; i++)
        res += D[tour[i]][tour[i+1]];
    res += D[tour[i]][tour[0]];

    return res;
}