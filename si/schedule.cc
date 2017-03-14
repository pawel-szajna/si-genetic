#include <algorithm>
#include <iterator>
#include <map>
#include <set>
#include <vector>

#include "si/task.hh"
#include "si/resource.hh"

#include "si/schedule.hh"

namespace si
{

task schedule::task_at(int task_id) 
{
	return tasks.at(task_id - 1);
}

resource schedule::resource_at(int resource_id) 
{
	return resources.at(resource_id - 1);
}

std::vector<int> schedule::satisfying(int task_id)
{
	std::vector<int> satisfying;
	task t = tasks.at(task_id - 1);
	for (auto& res : resources) {
		if (res.skills.find(t.skill) != res.skills.end() && res.skills[t.skill] >= t.skill_level) {
			satisfying.push_back(res.id);
		}
	}
	return satisfying;
}

void schedule::find_succesors()
{
	has_succesors = std::vector<bool>(tasks.size(), false);

	for (auto t : tasks) {
		for (auto p : t.predecessors) {
			has_succesors[p - 1] = true;
		}
	}
}

}
