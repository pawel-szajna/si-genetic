#include <algorithm>
#include <iterator>
#include <map>
#include <set>
#include <vector>

#include "schedule.hh"

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
	std::for_each(resources.begin(), resources.end(), [&t, &satisfying](resource res) {
		if (res.skills[t.skill] >= t.skill_level) {
			satisfying.push_back(res.id);
		}
	});
	return satisfying;
}

}
