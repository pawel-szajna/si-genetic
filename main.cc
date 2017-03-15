#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <random>
#include <set>
#include <vector>

#include "si/task.hh"
#include "si/resource.hh"
#include "si/schedule.hh"

#include "si/io/io.hh"

#include "si/schedulers/genetic.hh"
#include "si/schedulers/greedy.hh"

#include "util.hh"

using namespace si;

int main(int argc, char* argv[])
{
	double cross_prob = 0.01;
	double mutate_prob = 0.01;
	int population = 50;
	int epochs = 100;
	int sel_param = 5;
	bool debug = false;
	std::ofstream logfile;

	try {

		// Parse command line arguments

		int argument = 0;
		while (( ++argument ) * 2 < argc) {
			const char* argtext = argv[argument * 2 - 1];
			if (!strcmp(argtext, "-c")) {
				cross_prob = lexical_cast<double>( argv[argument * 2] );
			} else if (!strcmp(argtext, "-m")) {
				mutate_prob = lexical_cast<double>( argv[argument * 2] );
			} else if (!strcmp(argtext, "-p")) {
				population = lexical_cast<int>( argv[argument * 2] );
			} else if (!strcmp(argtext, "-e")) {
				epochs = lexical_cast<int>( argv[argument * 2] );
			} else if (!strcmp(argtext, "-s")) {
				sel_param = lexical_cast<int>( argv[argument * 2] );
			} else if (!strcmp(argtext, "-d")) {
				debug = lexical_cast<bool>( argv[argument * 2] );
			} else if (!strcmp(argtext, "-l")) {
				logfile.open(argv[argument * 2], std::ofstream::out);
			} else {
				std::cerr << "Unknown parameter: " << argv[argument * 2 - 1] << std::endl;
				return -1;
			}
		}

		// Do the scheduling

		si::schedule s = si::io::load(std::cin);
		si::schedulers::sample assignments;
		si::schedulers::sample times;
		
		s.find_succesors();
		
		si::schedulers::optimize(
			s, assignments, times, 
			population, epochs, cross_prob, mutate_prob, sel_param,
			si::schedulers::time_evaluator, 
			si::schedulers::tournament_selector, 
			logfile, debug
		);
		
		si::io::save(std::cout, s, assignments, times);

	} catch (const std::invalid_argument& e) {
		std::cerr << "Execution failed: " << e.what() << std::endl;
		return -1;
	}
}
