/*
 * main.cc
 *
 */

#include <iostream>
#include <set>
#include <vector>

#include "si/io/io.hh"
#include "si/schedulers/genetic.hh"

using namespace si;

int main(int argc, char* argv[])
{
	try {
		std::getchar();
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		std::getchar();
		return -1;
	}
}
