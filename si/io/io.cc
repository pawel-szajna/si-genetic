#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
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
	std::string line;
	schedule s;
	while (is.good()) {
		std::getline(is, line);
		if (lexical_cast<std::string>( line ) == "ResourceID") {
			while (is.good()) {
				std::getline(is, line);
				if (line.at(0) == '=') {
					break;
				}
				std::stringstream stream(line);
				int id, skill_level;
				double salary;
				std::string skill;
				std::map<std::string, int> skills;
				stream >> id >> salary;
				while (stream.good()) {
					stream >> skill;
					stream >> skill_level;
					skills.insert(std::pair<std::string, int>(skill, skill_level));
				}
				s.resources.push_back(resource(id, salary, skills));
			}
		}
		if (lexical_cast<std::string>( line ) == "TaskID") {
			while (is.good()) {
				std::getline(is, line);
				if (line.at(0) == '=') {
					return s;
				}
				std::stringstream stream(line);
				int id, duration, skill_level, pred_id;
				std::string skill;
				std::set<int> pred;
				pred.clear();
				stream >> id >> duration >> skill >> skill_level;
				while (stream.good()) {
					stream >> pred_id;
					if (stream.good()) {
						pred.emplace(pred_id);
					}
				}
				s.tasks.push_back(task(id, duration, skill, skill_level, pred));
			}
		}
	}
	throw std::invalid_argument("Bad input data format");
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
