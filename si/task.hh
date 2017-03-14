#ifndef TASK_HH
#define TASK_HH

namespace si
{

struct task
{
	int           duration;
	std::string	  skill;
	int           skill_level;
	std::set<int> predecessors;

	task(int duration, std::string skill, int skill_level, std::set<int> predecessors): duration(duration), skill(skill), skill_level(skill_level), predecessors(predecessors) {}

};

}

#endif 
