#include <functional>
#include <map>
#include <random>
#include <set>
#include <string>
#include <vector>

#include "si/resource.hh"
#include "si/task.hh"
#include "si/schedule.hh"
#include "si/schedulers/greedy.hh"

#include "genetic.hh"

#include <iostream>

namespace si::schedulers
{

population initialize(schedule& s, std::mt19937& gen, int pop, int tasks)
{
	population p(pop, std::vector<int>(tasks, -1));
	for (auto& individual : p) {
		for (int i = 0; i < tasks; ++i) {
			std::vector<int> valid = s.satisfying(i + 1);
			if (valid.empty()) {
				throw std::invalid_argument("No resource can solve task #" + std::to_string( i + 1 ));
			}
			std::uniform_int_distribution<> dis(0, valid.size() - 1);
			individual[i] = valid.at(dis(gen));
		}
	}
	return p;
}

void print_individual(sample& v)
{
	std::cout << "[ ";
	for (auto i : v) {
		std::cout << i << " ";
	}
	std::cout << "]\n";
}

int time_evaluator(schedule& s, sample& individual)
{
	int result = 0;
	sample times(individual.size(), 0);
	build_timestamps(s, individual, times);
	
	for (unsigned i = 0; i < individual.size(); ++i) {
		int current = s.task_at(i + 1).duration + times.at(i);
		if (current > result) {
			result = current;
		}
	}

	return result;
}

int cost_evaluator(schedule& s, sample& individual)
{
	int result = 0;

	for (unsigned i = 0; i < individual.size(); ++i) {
		result += (int)((double)(s.task_at(i + 1).duration) * s.resource_at(individual.at(i)).salary);
	}

	return result;
}

void optimize(schedule& s, sample& assignments, sample& times, int pop, int epochs, evaluator evaluate, selector select)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	int tasks = s.tasks.size();

	population p = initialize(s, gen, pop, tasks);

	for (auto& v : p) {
		print_individual(v);
	}
}



}
