#include <functional>
#include <map>
#include <numeric>
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

int roulette_selector(population p)
{
	return 0;
}

void evaluation(schedule& s, population p, sample& scores, evaluator evaluate, int& best, int& avg, int& worst)
{
	unsigned count = p.size();
	worst = std::numeric_limits<int>::min();
	best = std::numeric_limits<int>::max();
	avg = 0;

	for (unsigned i = 0; i < count; ++i) {
		int score = evaluate(s, p.at(i));
		scores[i] = score;
		avg += score;
		if (worst < score) worst = score;
		if (best > score) best = score;
	}

	avg /= count;
}

void optimize(schedule& s, sample& assignments, sample& times, int pop, int epochs, double cross_prob, double mutate_prob, evaluator evaluate, selector select)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	int tasks = s.tasks.size();
	int best, avg, worst;

	population p = initialize(s, gen, pop, tasks);
	sample scores(pop, 0);

	for (int epoch = 0; epoch < epochs; ++epoch) {
		evaluation(s, p, scores, evaluate, best, avg, worst);
		
		if(!((epoch+1) % 50)) std::cout << "Epoch #" << (epoch+1) << ", best=" << best << ", avg=" << avg << ", worst=" << worst << std::endl;
	}
}



}
