#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

#include "si/resource.hh"
#include "si/task.hh"
#include "si/schedule.hh"

#include "greedy.hh"

namespace si::schedulers
{

int earliest_time(schedule& s, std::vector<int>& times, int task_id)
{
	int earliest = 0;
	for (int p : s.task_at(task_id).predecessors) {
		task t = s.task_at(p);
		int pred_finish = times[t.id - 1] + t.duration;
		if (pred_finish > earliest) {
			earliest = pred_finish;
		}
	}
	return earliest;
}

void build_timestamps(schedule& s, std::vector<int>& assignments, std::vector<int>& times)
{
	std::vector<int> finish_times(s.resources.size(), 0);

	auto find_timestamps = [&assignments, &finish_times, &s, &times](task& t) {
		int earliest = earliest_time(s, times, t.id);
		int finish = finish_times[assignments[t.id - 1] - 1];
		times[t.id - 1] = std::max(earliest, finish);
		finish_times[assignments[t.id - 1] - 1] = times[t.id - 1] + t.duration;
	};
	
	for (auto& t : s.tasks) {
		if (s.has_succesors[t.id - 1]) {
			find_timestamps(t);
		}
	}

	for (auto& t : s.tasks) {
		if (!s.has_succesors[t.id - 1]) {
			find_timestamps(t);
		}
	}
}

}
