#include <iostream>
#include <map>
#include <set>
#include <vector>

#include "si/schedule.hh"
#include "util.hh"

#include "si/io/io.hh"

namespace si::io {

const char* separator = "==========================================================";

schedule load(std::istream& is)
{
	return schedule();
}

void save(std::ostream& os, schedule& s)
{
}

}
