#ifndef IO_HH
#define IO_HH

#include <vector>
#include <map>

#include "si/schedule.hh"

namespace si
{

namespace io
{

schedule load(std::istream& is);
void save(std::ostream& os, schedule& s);

}

}

#endif
