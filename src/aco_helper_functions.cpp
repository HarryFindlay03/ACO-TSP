#include "../include/aco_helper_functions.hpp"

//
// ANT SYSTEM SETUP FUNCTIONS
//

ANT_DATA* generate_ant_data(const char* filename, int num_ants, int num_cities, int use_heuristic)
{
    ANT_DATA* ant_data = new ANT_DATA;
    ant_data->D = generate_distance_matrix(filename, num_cities);
    ant_data->T = generate_pheremone_matrix(ant_data->D, num_ants, num_cities, use_heuristic);
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

float** generate_pheremone_matrix(float** D, int num_ants, int num_cities, int use_heuristic)
{
    // ensure prng has been seeded well prior to calling this function
    float** pheremone_matrix = new float*[num_cities];

    // nearest neighbour tour heuristic value (num_cities / shortest NN tour)
    float nn_tour_heurisitc = (num_ants / shortest_nn_tour(D, num_cities));

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
            if(use_heuristic) 
                pheremone_matrix[i][j] = nn_tour_heurisitc;
            else
                pheremone_matrix[i][j] = (float)rand() / (float)RAND_MAX; // init between 0 and 1
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

    // ERROR HANDLING MUST BE DONE BEFORE THIS
    if(!doc.load_file(filename))
    {
        std::cout << "ERROR - FILENAME NOT VALID!" << std::endl;
        std::exit(-1);
    }

    pugi::xml_node nodes = doc.child("travellingSalesmanProblemInstance").child("graph");

    // counting how many vertexes in the graph there are
    int node_count = 0;
    pugi::xml_node node;
    for(node = nodes.first_child(); node; node = node.next_sibling())
        node_count++;

    return node_count;
}

//
// NEAREST NEIGHBOUR HEURISTIC
//

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
    float res = helper_tour_length(D, nn_tour, num_cities);

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

float helper_tour_length(float** D, int* tour, int num_cities)
{
    float res = 0;

    int i;
    for(i = 0; i < num_cities-1; i++)
        res += D[tour[i]][tour[i+1]];
    res += D[tour[i]][tour[0]];

    return res;
}

//
// VALIDITY CHECKS
//

int tour_valid(int* tour, int num_cities)
{
    int i, j, count, curr;
    for(i = 0; i < num_cities; i++)
    {
        count = 0;
        for(j = 0; j < num_cities; j++)
        {
            if(tour[j] == tour[i])
            {
                count++;
            }
        }
        if(count != 1)
            return 0;
    }

    return 1;
}

//
// MISC HELP FUNCTIONS
//

int copy_shortest(float** D, int* shortest, int* generation_shortest, int num_cities)
{
    if(!(helper_tour_length(D, generation_shortest, num_cities) < helper_tour_length(D, shortest, num_cities)))
        return 0;

    int i;
    for(i = 0; i < num_cities; i++)
        shortest[i] = generation_shortest[i];

    return 1;
}

int is_valid_xml_filename(std::string& filename)
{
    // filename error handling
    int errNo = 0;
    pugi::xml_document doc;
    while(!doc.load_file(filename.c_str()))
    {
        if(errNo++ >= 5)
        {
            std::cout << "YOU HAVE ENTERED TOO MANY WRONG FILENAMES\nEXITING" << std::endl;
            std::exit(-1);
        }
        std::cout << "THAT IS NOT A VALID TSP INSTANCE XML FILENAME! (" << errNo << "/" << 5 << ")" << std::endl;
        std::cout << "PLEASE TRY AGAIN, ENTER ONE HERE (from program root): ";
        std::cin >> filename;
    }

    return 1;
}

int is_valid_param_filename(std::string& filename)
{
    // filename error handling
    int errNo = 0;
    std::ifstream param_file(filename);
    while(!(is_txt_file(filename)) || !(param_file.is_open()))
    {
        if(errNo++ >= 5)
        {
            std::cout << "YOU HAVE ENTERED TOO MANY WRONG FILENAMES\nEXITING" << std::endl;
            return 0; 
        }
        std::cout << "THAT IS NOT A VALID PARAMETER FILENAME! (" << errNo << "/" << 5 << ")" << std::endl;
        std::cout << "PLEASE TRY AGAIN, ENTER ONE HERE (from program root): ";
        std::cin >> filename;

        param_file.open(filename);
    }

    param_file.close();
    return 1; 
}

int is_txt_file(std::string& filename)
{
    int i, pos;
    for(i = 0; i < filename.length(); i++)
    {
        if(filename[i] == '.')
        {
            if(filename.substr(i+1, 3) == "txt")
                return 1;
            return 0;
        }
    }

    return 0;
}

int get_params(std::string& filename, float* params)
{
    std::string line;
    std::ifstream param_file(filename);

    int line_num = 0;
    if(param_file.is_open())
    {
        while(getline(param_file, line))
        {
            if(line_num >= 9)
            {
                std::cout << "PARAM FILE NOT FORMATTED CORRECTLY!" << std::endl;
                std::cout << "USING DEFAULT VALUES FOR NOW, TO USE PARAM FILE IN THE FUTURE PLEASE";
                std::cout << " CHECK THE README AND REFORMAT CORRECTLY!" << std::endl;
                return 0;
            }

            std::string delim = "=";
            line.erase(0, line.find(delim) + delim.length());
            params[line_num] = std::stof(line);
            line_num++;
        }
    }

    if (line_num != 9)
    {
        std::cout << "PARAM FILE NOT FORMATTED CORRECTLY!" << std::endl;
        std::cout << "USING DEFAULT VALUES FOR NOW, TO USE PARAM FILE IN THE FUTURE PLEASE";
        std::cout << " CHECK THE README AND REFORMAT CORRECTLY!" << std::endl;
        return 0;
    }

    param_file.close();
    return 1;
}

void clean_up(ANT_DATA* ant_data)
{
    int num_cities = *(ant_data->num_cities);
    int num_ants = *(ant_data->num_ants);

    int i;

    // cleanup distance matrix
    for(i = 0; i < num_cities; i++)
        delete[] (ant_data->D)[i];
    delete[] (ant_data->D);

    // cleanup pheremone matrix
    for(i = 0; i < num_cities; i++)
        delete[] (ant_data->T)[i];
    delete[] (ant_data->T);

    // cleanup ant map
    for(i = 0; i < num_ants; i++)
        delete[] (ant_data->ant_map)[i];
    delete[] (ant_data->ant_map);

    // cleanup ant routes
    for(i = 0; i < num_ants; i++)
        delete[] (ant_data->ant_routes)[i];
    delete[] (ant_data->ant_routes);

    // cleanup num_cities, num_ants
    delete (ant_data->num_cities);
    delete (ant_data->num_ants);

    // final cleanup ant_data
    delete ant_data;

    return;
}