#include <algorithm>
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

std::string sample_text(sample& s)
{
	std::string t;
	for (auto& i : s) {
		t += std::to_string(i);
	}
	return t;
}

int random_valid_resource(schedule& s, std::mt19937& gen, int id)
{
	std::vector<int> valid = s.satisfying(id + 1);
	if (valid.empty()) {
		throw std::invalid_argument("No resource can solve task #" + std::to_string(id + 1));
	}
	return valid.at(std::uniform_int_distribution<>(0, valid.size() - 1)( gen ));
}

population initialize(schedule& s, std::mt19937& gen, int pop, int tasks)
{
	population p(pop, std::vector<int>(tasks, -1));
	for (auto& individual : p) {
		for (int i = 0; i < tasks; ++i) {
			individual[i] = random_valid_resource(s, gen, i);
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
		int current = s.tasks.at(i).duration + times.at(i);
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
		result += (int)((double)(s.tasks.at(i).duration) * s.resources.at(individual.at(i) - 1).salary);
	}

	return result;
}

int tournament_selector(sample scores, std::mt19937& gen, int ind_count, bool d)
{
	int length = scores.size();
	int best = -1, best_score = std::numeric_limits<int>::max();
	std::set<int> individuals;
	std::uniform_int_distribution<> distribution(0, length - 1);

	if(d) std::cerr << "Tournament: { ";

	while (individuals.size() < ind_count) {
		individuals.emplace(distribution(gen));
	}

	for (auto& i : individuals) {
		if(d) std::cerr << i << ":" << scores.at(i) << " ";
		if (scores.at(i) < best_score) {
			best_score = scores.at(i);
			best = i;
		}
	}

	if(d) std::cerr << "}, chose " << best << ":" << best_score << std::endl;

	return best;
}

int roulette_selector(sample scores, std::mt19937& gen, int scale, bool d)
{
	int max = *std::max_element(scores.begin(), scores.end());
	int min = *std::min_element(scores.begin(), scores.end());

	for (auto& i : scores) {
		i = max - i + (min / scale);
	}

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

int evaluation(schedule& s, population& p, sample& scores, evaluator evaluate, int& best, int& avg, int& worst, int& best_id, int& worst_id, bool d)
{
	unsigned count = p.size();
	worst = std::numeric_limits<int>::min();
	best = std::numeric_limits<int>::max();
	avg = 0;

	if(d) std::cerr << "Evaluation: [ ";

	for (unsigned i = 0; i < count; ++i) {
		int score = evaluate(s, p.at(i));
		if(d) std::cerr << sample_text(p.at(i)) << ":" << score << " ";
		scores[i] = score;
		avg += score;
		if (worst < score) {
			worst = score;
			worst_id = i;
		}
		if (best > score) {
			best = score;
			best_id = i;
		}
	}

	if(d) std::cerr << "]" << std::endl;
	
	avg /= count;
}

void crossover(population& p, sample& first, sample& second, double probability, std::mt19937& gen, bool d)
{
	if (std::uniform_real_distribution<>(0, 1)( gen ) < probability) {
		int length = first.size();
		int cut = std::uniform_int_distribution<>(1, length - 2)(gen);

		if(d) std::cerr << "Crossover: " << sample_text(first) << "x" << sample_text(second) << "@" << cut << " = ";

		for (int i = cut; i < length; ++i) {
			std::swap((first)[i], (second)[i]);
		}

		if(d) std::cerr << sample_text(first) << ", " << sample_text(second) << std::endl;
	}
}

sample mutation(schedule& s, sample individual, double mutate_prob, std::mt19937& gen, bool d)
{
	std::uniform_real_distribution<> distribution(0, 1);
	for (int i = 0; i < individual.size(); ++i) {
		if (distribution(gen) < mutate_prob) {
			if(d) std::cerr << "Mutating " << sample_text(individual) << "@" << i << " to ";
			individual[i] = random_valid_resource(s, gen, i);
			if(d) std::cerr << sample_text(individual) << std::endl;
		}
	}
	return individual;
}

void optimize(schedule& s, sample& assignments, sample& times, int pop, int epochs, double cross_prob, double mutate_prob, int sel_param, evaluator evaluate, selector select, std::ostream& log, bool d)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	if (pop % 2) ++pop;

	int tasks = s.tasks.size();
	int best, avg, worst, best_id, worst_id;
	int step = epochs / 20;

	population p = initialize(s, gen, pop, tasks);
	sample scores(pop, 0);
	evaluation(s, p, scores, evaluate, best, avg, worst, best_id, worst_id, d);

	for (int epoch = 0; epoch < epochs; ++epoch) {
		population new_population;
		while (new_population.size() < pop) {
			sample child1 = p.at(select(scores, gen, sel_param, d));
			sample child2 = p.at(select(scores, gen, sel_param, d));
			crossover(p, child1, child2, cross_prob, gen, d);
			new_population.push_back(mutation(s, child1, mutate_prob, gen, d));
			new_population.push_back(mutation(s, child2, mutate_prob, gen, d));
		}
		p = new_population;
		evaluation(s, p, scores, evaluate, best, avg, worst, best_id, worst_id, d);
		log << (epoch + 1) << "," << best << "," << avg << "," << worst << std::endl;
		if (!( epoch % step )) std::cerr << ( 100 * epoch / epochs ) << "%" << std::endl;
	}

	assignments = p.at(best_id);
	times = sample(tasks, 0);
	build_timestamps(s, assignments, times);
}



}
