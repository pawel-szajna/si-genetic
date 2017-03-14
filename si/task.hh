#ifndef TASK_HH
#define TASK_HH

namespace si
{

struct task
{
	int           id;
	int           duration;
	std::string	  skill;
	int           skill_level;
	std::set<int> predecessors;

	task(int id, int duration, std::string skill, int skill_level, std::set<int> predecessors): id(id), duration(duration), skill(skill), skill_level(skill_level), predecessors(predecessors) {}

};

}

#endif 
