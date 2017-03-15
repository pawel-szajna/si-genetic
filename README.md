# si-genetic

A C++ implementation of a genetic algorithm solving a multi-skill resource-constrained project scheduling problem.

This implementation relies on some modern C++ features up to C++17.

## Usage

The application is a command line utility that reads the input data from standard input and outputs the results to standard output. Several configuration options are provided:

* `-c` crossing probability, default: 0.01
* `-m` mutation probability, default: 0.01
* `-p` population size, default: 50
* `-e` epochs, default: 100
* `-s` selection function parameter, default: 5
* `-l` filename for optional CSV output
* `-d` enables debug output when set to 1, default: 0
* `-ev` sets the evaluator function, options available: `time`, `cost`
* `-sel` sets the selection function, options available: `roulette`, `tournament`
