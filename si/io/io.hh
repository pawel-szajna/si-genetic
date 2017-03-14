#ifndef IO_HH
#define IO_HH

namespace si::io
{

schedule load(std::istream& is);
void     save(std::ostream& os, schedule& s, std::vector<int>& assignments, std::vector<int>& times);

}

#endif
