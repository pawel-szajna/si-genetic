/*
 * main.cc
 *
 */

#include <iostream>

#include "si/io/io.hh"
#include "si/schedulers/genetic.hh"

#include "util.hh"

#include <vector>

int main(int argc, char* argv[])
{
	try {
		//auto s = si::io::load(std::cin);


		//si::io::save(std::cout, s);

		std::getchar();
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		std::getchar();
		return -1;
	}
}
