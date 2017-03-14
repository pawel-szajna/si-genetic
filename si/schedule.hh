#ifndef SCHEDULE_HH
#define SCHEDULE_HH

#include "si/task.hh"
#include "si/resource.hh"

namespace si
{

struct schedule
{
	std::vector<task>     tasks;
	std::vector<resource> resources;

	std::vector<int> assigned_resources;
	std::vector<int> assigned_hours;

	task      task_at(int task_id);
	resource  resource_at(int resource_id);
	std::vector<int> satisfying(int task_id);
};

}

#endif
