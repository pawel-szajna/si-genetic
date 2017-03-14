#include <fstream>
#include <functional>
#include <iostream>
#include <map>
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
	std::ofstream logfile;

	try {

		// Parse command line arguments

		int argument = 0;
		while (( ++argument ) * 2 - 1 < argc) {
			const char* argtext = argv[argument * 2 - 1];
			if (!strcmp(argtext, "-c")) {
				cross_prob = lexical_cast<double>( argv[argument * 2] );
			} else if (!strcmp(argtext, "-m")) {
				mutate_prob = lexical_cast<double>( argv[argument * 2] );
			} else if (!strcmp(argtext, "-p")) {
				population = lexical_cast<int>( argv[argument * 2] );
			} else if (!strcmp(argtext, "-e")) {
				epochs = lexical_cast<int>( argv[argument * 2] );
			} else if (!strcmp(argtext, "-l")) {
				logfile.open(argv[argument * 2], std::ofstream::out);
			} else {
				std::cerr << "Unknown parameter: " << argv[argument * 2 - 1] << std::endl;
				return -1;
			}
		}

		// Do the scheduling

		si::schedule s;
		si::schedulers::sample assignments;
		si::schedulers::sample times;

		s.tasks.push_back(task(1, 37, "Q1", 0, {}));
		s.tasks.push_back(task(2, 8, "Q1", 0, {}));
		s.tasks.push_back(task(3, 9, "Q4", 2, { 1 }));
		s.tasks.push_back(task(4, 26, "Q1", 2, {}));
		s.tasks.push_back(task(5, 30, "Q1", 2, { 4,3 }));
		s.tasks.push_back(task(6, 18, "Q4", 2, {}));
		s.tasks.push_back(task(7, 27, "Q2", 1, { 6 }));
		s.tasks.push_back(task(8, 24, "Q1", 2, { 2 }));
		s.tasks.push_back(task(9, 10, "Q3", 0, { 4 }));
		s.tasks.push_back(task(10, 29, "Q3", 1, { 1 }));

		s.resources.push_back(resource(1, 59.7, { {"Q0",2},{"Q3",1},{"Q1",1} }));
		s.resources.push_back(resource(2, 75.9, { {"Q0",1},{"Q4",1},{"Q1",1} }));
		s.resources.push_back(resource(3, 69.8, { {"Q2",1},{"Q4",2},{"Q1",0} }));
		s.resources.push_back(resource(4, 22.4, { {"Q4",1},{"Q0",1},{"Q3",0} }));
		s.resources.push_back(resource(5, 32.6, { {"Q4",1},{"Q1",2},{"Q3",1} }));

		s.find_succesors();
		
		si::schedulers::optimize(s, assignments, times, population, epochs, cross_prob, mutate_prob, si::schedulers::time_evaluator, [](auto i) {return 0; }, logfile);
		si::io::save(std::cout, s, assignments, times);

		std::getchar();
	} catch (const std::invalid_argument& e) {
		std::cerr << "Execution failed: " << e.what() << std::endl;
		std::getchar();
		return -1;
	}
}
