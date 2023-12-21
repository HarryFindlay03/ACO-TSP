#include <ctime>
#include <string>

#include "aco_helper_functions.hpp"
#include "aco_functions.hpp"
#include "aco_experiment_functions.hpp"

/**
 * @brief run ACO experiment with logging that outputs to a results file
 * 
 * @param filename location of file storing city information
 * @param alpha parameter affecting weighting of pheremone
 * @param beta parameter affecting weighting of distance heuristic
 * @param Q parameter affecting the return of distance heuristic
 * @param evaporation_rate parameter affecting evaporation rate
 * @param num_ants number of ants to be used in the system
 * @param num_cities number of cities from the file
 * @param iterations number of iterations to run the ant route finding for
 * @param file_extra parameter to vary
 * 
 */
void run_with_logging(std::string&, float, float, float, float, int, int, int, std::string file_extra = "0");

/**
 * @brief run ACO experiment with per iteration logging to file 
 * 
 * @param filename location of file storing city information
 * @param alpha parameter affecting weighting of pheremone
 * @param beta parameter affecting weighting of distance heuristic
 * @param Q parameter affecting the return of distance heuristic
 * @param evaporation_rate parameter affecting evaporation rate
 * @param num_ants number of ants to be used in the system
 * @param num_cities number of cities from the file
 * @param iterations number of iterations to run the ant route finding for
 * @param approach_type (optional, default = 1) the ACO approach to use. 1 = classic As, 2 = elitist AS.
 * @param output_ext (optional, default = default) the string to attach to the end of the filename for easy differentiation to other results.
 * 
 */
void run_with_per_iteration_logging(std::string& filename, float alpha, float beta, float Q, float evaporation_rate, int num_ants, int num_cities, int iterations, int approach_type=0, std::string output_ext = "default");