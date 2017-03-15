#ifndef IO_HH
#define IO_HH

namespace si::io
{

typedef journey schedule;
schedule load(std::istream& is);
void     save(std::ostream& os, schedule& s, std::vector<int>& assignments);

}

#endif
