#ifndef RESOURCE_HH
#define RESOURCE_HH

namespace si
{

struct resource
{
	int    id;
	double salary;

	std::map<std::string, int> skills;

	resource(int id, double salary, std::map<std::string, int> skills): id(id), salary(salary), skills(skills) {}
};

}

#endif
