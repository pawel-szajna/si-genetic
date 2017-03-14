#ifndef GENETIC_HH
#define GENETIC_HH

namespace si::schedulers
{

//template<typename F1, typename F2>
void optimize(schedule& s, std::vector<int>& assignments, std::vector<int>& times, int pop, int epochs /*, F1 evaluate, F2 select*/);

}

#endif
