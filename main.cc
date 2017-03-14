/*
 * main.cc
 *
 * Sztuczna inteligencja – zadanie 1: algorytmy genetyczne
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
		std::vector<int> a{ 1,2,3,4,5 };
		std::vector<int> b{ 6,7,8,9,0 };
		std::swap(a[4], b[4]);
		for (auto& i : a) std::cout << i << " ";
		std::cout << "\n";
		for (auto& i : b) std::cout << i << " ";
		std::cout << "\n";

		//si::io::save(std::cout, s);

		std::getchar();
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		std::getchar();
		return -1;
	}
}
