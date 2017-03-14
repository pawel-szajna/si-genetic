#ifndef TASK_HH
#define TASK_HH

namespace si
{

struct task
{
	int	          duration;
	std::string	  skill;
	int	          skill_level;
	std::set<int> predecessors;
};

}

#endif 
