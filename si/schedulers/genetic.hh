#ifndef GENETIC_HH
#define GENETIC_HH

namespace si::schedulers
{

typedef journey schedule;
typedef std::vector<int> sample;
typedef std::vector<std::vector<int>> population;
typedef std::function<int(schedule&, sample&)> evaluator;
typedef std::function<int(sample&, std::mt19937&, int, bool)> selector;

void optimize(
	schedule& s, 
	sample& assignments,
	int pop, int epochs, double cross_prob, double mutate_prob, int sel_param,
	evaluator evaluate, selector select,
	std::ostream& log, bool debug
);

int distance_evaluator(schedule& s, sample& individual);

int roulette_selector(sample& scores, std::mt19937& gen, int scale, bool d);
int tournament_selector(sample& scores, std::mt19937& gen, int ind_count, bool d);

}

#endif
