#include <iostream>

#include "si/schedule.hh"

#include "si/io/io.hh"

namespace si {

namespace io {

const char* separator = "==========================================================";

schedule load(std::istream& is)
{
	return schedule();
}

void save(std::ostream& os, schedule& s)
{
}

}

}