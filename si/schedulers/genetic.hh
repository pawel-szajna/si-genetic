#ifndef GENETIC_HH
#define GENETIC_HH

namespace si::schedulers
{

typedef std::vector<int> sample;
typedef std::vector<std::vector<int>> population;
typedef std::function<int(schedule&, sample&)> evaluator;
typedef std::function<int(population)> selector;

void optimize(schedule& s, sample& assignments, sample& times, int pop, int epochs, evaluator evaluate, selector select);

int time_evaluator(schedule& s, sample& individual);
int cost_evaluator(schedule& s, sample& individual);

}

#endif
