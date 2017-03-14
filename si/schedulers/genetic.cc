#include <map>
#include <random>
#include <set>
#include <vector>

#include "si/resource.hh"
#include "si/task.hh"
#include "si/schedule.hh"

#include "genetic.hh"

#include <iostream>

namespace si::schedulers
{

typedef std::vector<std::vector<int>> population;

//template<typename F1, typename F2>
void optimize(schedule& s, std::vector<int>& assignments, std::vector<int>& times, int pop, int epochs /*F1 evaluate, F2 select*/)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	int tasks = s.tasks.size();

	population p(pop, std::vector<int>(tasks, -1));
	for (auto& individual : p) {
		for (int i = 0; i < tasks; ++i) {
			std::vector<int> valid = s.satisfying(i + 1);
			if (valid.empty()) {
				throw std::invalid_argument("No resource can solve task #" + ( i + 1 ));
			}
			std::uniform_int_distribution<> dis(0, valid.size() - 1);
			individual[i] = valid.at(dis(gen));
		}
	}

	for (auto& v : p) {
		std::cout << "[ ";
		for (auto i : v) {
			std::cout << i << " ";
		}
		std::cout << "]\n";
	}
}

}
