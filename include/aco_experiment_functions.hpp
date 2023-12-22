//
// RELEVANT INCLUDES
//

#include <fstream>

#include "aco_functions.hpp"
#include "aco_helper_functions.hpp"

//
// EXPERIMENT FUNCTIONS
//

/**
 * @brief run classic ant system optimisation with given parameters, handles own memory
 * independently and clears up after function has completed.
 * 
 * Outputs information to the console <tour length>, <number of iterations / total iterations>, <tour>
 * 
 * @param filename location of file storing city information
 * @param alpha parameter affecting weighting of pheremone
 * @param beta parameter affecting weighting of distance heuristic
 * @param Q parameter affecting the return of distance heuristic
 * @param evaporation_rate parameter affecting evaporation rate
 * @param num_ants number of ants to be used in the system
 * @param num_cities number of cities from the file
 * @param iterations number of iterations to run the ant route finding for
 * @param file_extra parameter to vary - if left empty then experiment will not be ran 
 * @param use_heuristic (optional, default=1) if false then random number between 0 and 1 set for each pos in pheremone matrix.
 * If true, nearest neighbour heuristic is used.
 * @param iteration_logging (optional, default=0) if false then iteration logging not enabled, if true then iteration logging enabled where it writes to a file with column
 * names (Retry, LengthOfOptima, IterationAt)
 */
void run_ant_system(std::string&, float, float, float, float, int, int, int, std::string file_extra = "0", int use_heuristic=1, int iteration_logging=0);

/**
 * @brief run elitist ant system optimisation with given parameters, handles own memory
 * independently and clears up after function has completed.
 * 
 * Outputs information to the console <tour length>, <number of iterations / total iterations>, <tour>
 * 
 * @param filename location of file storing city information
 * @param alpha parameter affecting weighting of pheremone
 * @param beta parameter affecting weighting of distance heuristic
 * @param Q parameter affecting the return of distance heuristic
 * @param evaporation_rate parameter affecting evaporation rate
 * @param e parameter affecting the amount of reinforcement by the best-so-far ant
 * @param num_ants number of ants to be used in the system
 * @param num_cities number of cities from the file
 * @param iterations number of iterations to run the ant route finding for
 * @param file_extra parameter to vary - if left empty then experiment will not be ran 
 * @param use_heuristic (optional, default=1) if false then random number between 0 and 1 set for each pos in pheremone matrix.
 * If true, nearest neighbour heuristic is used.
 * @param iteration_logging (optional, default=0) if false then iteration logging not enabled, if true then iteration logging enabled where it writes to a file with column
 * names (Retry, LengthOfOptima, IterationAt) 
 */
void run_ant_system_elitist(std::string&, float, float, float, float, float, int, int, int, std::string file_extra = "0", int use_heuristic=1, int iteration_logging=0);