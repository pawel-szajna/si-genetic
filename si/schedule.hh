#ifndef SCHEDULE_HH
#define SCHEDULE_HH

#include "si/task.hh"
#include "si/resource.hh"

namespace si
{

struct schedule
{
	std::map<int, task>		tasks;
	std::map<int, resource> resources;

	std::vector<int> assigned_resources;
	std::vector<int> assigned_hours;
};

}

#endif
