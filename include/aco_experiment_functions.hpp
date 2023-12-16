#include "aco_functions.hpp"
#include "aco_helper_functions.hpp"

/**
 * @brief run classic ant system optimisation with given parameters, handles own memory
 * independently and clears up after function has completed.
 * 
 * Outputs information to the console <tour length>, <number of iterations / total iterations>, <tour>
 * 
 * @param filename location of file storing city information
 * @param alpha parameter affecting weighting of pheremone
 * @param beta parameter affecting weighting of distance heuristic
 * @param Q parameter affecting evaporation depositing
 * @param evaporation_rate parameter affecting evaporation rate
 * @param num_ants number of ants to be used in the system
 * @param num_cities number of cities from the file
 * @param iterations number of iterations to run the ant route finding for
 */
void run_ant_system(std::string, float, float, float, float, int, int, int);

/**
 * @brief run elitist ant system optimisation with given parameters, handles own memory
 * independently and clears up after function has completed.
 * 
 * Outputs information to the console <tour length>, <number of iterations / total iterations>, <tour>
 * 
 * @param filename location of file storing city information
 * @param alpha parameter affecting weighting of pheremone
 * @param beta parameter affecting weighting of distance heuristic
 * @param Q parameter affecting the amount of pheremone to be deposited during lay_pheremone.
 * @param evaporation_rate parameter affecting evaporation rate
 * @param num_ants number of ants to be used in the system
 * @param num_cities number of cities from the file
 * @param iterations number of iterations to run the ant route finding for
 */
void run_elitist_ant_system(std::string, float, float, float, float, int, int, int);