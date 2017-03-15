#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "si/city.hh"
#include "si/journey.hh"

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
		std::stringstream ss(line);
		if (lexical_cast<std::string>( line ) == "EOF") return s;
		int id;
		double x, y;
		ss >> id >> x >> y;
		s.cities.push_back(city(id, x, y));
	}
	throw std::invalid_argument("Bad input format");
}

void save(std::ostream& os, schedule& s, std::vector<int>& assignments)
{
	for (auto& i : assignments) {
		os << i << std::endl;
	}
}

}
