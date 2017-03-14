#include <iostream>
#include <vector>
#include <map>

#include "si/schedule.hh"

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
