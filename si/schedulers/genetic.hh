#ifndef GENETIC_HH
#define GENETIC_HH

namespace si::schedulers
{

typedef std::vector<int> sample;
typedef std::vector<std::vector<int>> population;
typedef std::function<int(schedule&, sample&)> evaluator;
typedef std::function<int(sample, std::mt19937&, int)> selector;

void optimize(
	schedule& s, 
	sample& assignments, sample& times, 
	int pop, int epochs, double cross_prob, double mutate_prob, int sel_param,
	evaluator evaluate, selector select,
	std::ostream& log
);

int time_evaluator(schedule& s, sample& individual);
int cost_evaluator(schedule& s, sample& individual);

int roulette_selector(sample scores, std::mt19937& gen, int scale);
int tournament_selector(sample scores, std::mt19937& gen, int ind_count);

}

#endif
