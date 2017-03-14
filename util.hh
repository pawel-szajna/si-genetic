#ifndef UTIL_HH
#define UTIL_HH

#include <string>
#include <sstream>

// prawie jak boost
template<typename T>
T lexical_cast(std::string value)
{
	T result;
	std::stringstream stream(value);
	stream >> result;

	if (!stream) {
		throw std::invalid_argument("lexical cast failed, argument was '" + value + "'");
	}

	return result;
}

#endif
