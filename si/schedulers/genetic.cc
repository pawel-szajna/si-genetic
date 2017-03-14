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

int random_valid_resource(schedule& s, std::mt19937& gen, int task_id)
{
	std::vector<int> valid = s.satisfying(task_id);
	if (valid.empty()) {
		throw std::invalid_argument("No resource can solve task #" + std::to_string(task_id));
	}
	return valid.at(std::uniform_int_distribution<>(0, valid.size() - 1)( gen ));
}

population initialize(schedule& s, std::mt19937& gen, int pop, int tasks)
{
	population p(pop, std::vector<int>(tasks, -1));
	for (auto& individual : p) {
		for (int i = 0; i < tasks; ++i) {
			individual[i] = random_valid_resource(s, gen, i + 1);
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

int roulette_selector(sample& scores, std::mt19937& gen)
{
	int sum = std::accumulate(scores.begin(), scores.end(), 0);
	int target = std::uniform_int_distribution<>(0, sum - 1)( gen );
	int current = 0;

	for (unsigned i = 0; i < scores.size(); ++i) {
		if (current + scores.at(i) > target) {
			return i;
		}
		current += scores.at(i);
	}
}

int evaluation(schedule& s, population p, sample& scores, evaluator evaluate, int& best, int& avg, int& worst)
{
	unsigned count = p.size();
	unsigned best_id = -1;
	worst = std::numeric_limits<int>::min();
	best = std::numeric_limits<int>::max();
	avg = 0;

	for (unsigned i = 0; i < count; ++i) {
		int score = evaluate(s, p.at(i));
		scores[i] = score;
		avg += score;
		if (worst < score) worst = score;
		if (best > score) {
			best = score;
			best_id = i;
		}
	}
	
	avg /= count;
	return best_id;
}

void crossover(population& p, int first, int second, double probability, std::mt19937& gen)
{
}

void mutation(schedule& s, sample& individual, double mutate_prob, std::mt19937& gen)
{
	std::uniform_real_distribution<> distribution(0, 1);
	for (int i = 0; i < individual.size(); ++i) {
		if (distribution(gen) < mutate_prob) {
			individual[i] = random_valid_resource(s, gen, i + 1);
		}
	}
}

void optimize(schedule& s, sample& assignments, sample& times, int pop, int epochs, double cross_prob, double mutate_prob, evaluator evaluate, selector select, std::ostream& log)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	int tasks = s.tasks.size();
	int best, avg, worst, best_id;

	population p = initialize(s, gen, pop, tasks);
	sample scores(pop, 0);
	best_id = evaluation(s, p, scores, evaluate, best, avg, worst);
	log << "epoch;best;avg;worst" << std::endl;

	for (int epoch = 0; epoch < epochs; ++epoch) {
		int selected = select(scores, gen);
		crossover(p, selected, select(scores, gen), cross_prob, gen);
		mutation(s, p[selected], mutate_prob, gen);
		best_id = evaluation(s, p, scores, evaluate, best, avg, worst);
		log << (epoch + 1) << ";" << best << ";" << avg << ";" << worst << std::endl;
	}

	assignments = p.at(best_id);
	times = sample(tasks, 0);
	build_timestamps(s, assignments, times);
}



}
