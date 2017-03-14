#ifndef SCHEDULE_HH
#define SCHEDULE_HH

namespace si
{

struct schedule
{
	std::vector<task>     tasks;
	std::vector<resource> resources;
	std::vector<bool>     has_succesors;

	task             task_at(int task_id);
	resource         resource_at(int resource_id);
	std::vector<int> satisfying(int task_id);
	void             find_succesors();
};

}

#endif
