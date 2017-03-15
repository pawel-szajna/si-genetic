#include <fstream>
#include <functional>
#include <iostream>
#include <random>
#include <vector>

#include "si/city.hh"
#include "si/journey.hh"

#include "si/io/io.hh"

#include "si/schedulers/genetic.hh"

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
	si::schedulers::selector selector = si::schedulers::tournament_selector;

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
			} else if (!strcmp(argtext, "-sel")) {
				if (!strcmp(argv[argument * 2], "roulette")) {
					selector = si::schedulers::roulette_selector;
				} else if (!strcmp(argv[argument * 2], "tournament")) {
					selector = si::schedulers::tournament_selector;
				} else {
					throw std::invalid_argument("Invalid selector function: " + std::string(argv[argument * 2]));
				}
			} else if (!strcmp(argtext, "-l")) {
				logfile.open(argv[argument * 2], std::ofstream::out);
			} else {
				std::cerr << "Unknown parameter: " << argv[argument * 2 - 1] << std::endl;
				return -1;
			}
		}

		// Do the scheduling

		si::journey j = si::io::load(std::cin);
		si::schedulers::sample assignments;
		
		si::schedulers::optimize(
			j, assignments, 
			population, epochs, cross_prob, mutate_prob, sel_param,
			si::schedulers::distance_evaluator, selector, 
			logfile, debug
		);
		
		si::io::save(std::cout, j, assignments);

	} catch (const std::invalid_argument& e) {
		std::cerr << "Execution failed: " << e.what() << std::endl;
		return -1;
	}
}
