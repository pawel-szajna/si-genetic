#ifndef GREEDY_HH
#define GREEDY_HH

namespace si::schedulers
{

int  earliest_time(schedule& s, std::vector<int>& times, int task_id);
void build_timestamps(schedule& s, std::vector<int>& assignments, std::vector<int>& times);

}

#endif 
