#include <iostream>
#include <map>
#include <set>
#include <vector>

#include "si/task.hh"
#include "si/resource.hh"
#include "si/schedule.hh"

#include "util.hh"

#include "si/io/io.hh"

namespace si::io {

const char* separator = "==========================================================";

schedule load(std::istream& is)
{
	return schedule();
}

void save(std::ostream& os, schedule& s, std::vector<int>& assignments, std::vector<int>& times)
{
	os << "Hour \t Resource assignments (resource ID - task ID) \n";

	std::map<int, std::vector<int>> hours;

	for (unsigned i = 0; i < times.size(); ++i) {
		int time = times.at(i);
		if (hours.find(time) == hours.end()) {
			hours.insert(std::pair<int, std::vector<int>>{ time, std::vector<int>() });
		}
		hours.at(time).push_back(i);
	}

	for (auto p : hours) {
		os << p.first << " ";
		for (auto t : p.second) {
			os << assignments.at(t) << "-" << ( t + 1 ) << " ";
		}
		os << "\n";
	}
}

}
