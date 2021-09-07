#--------------------------------------------------------------------------#
# Name: Jan Koziol                                                         #
# Email: jankoziol@gmx.de                                                  #
# GitHub: https://github.com/Jankoziol/discrete-sample                     #
#--------------------------------------------------------------------------#

CXXFLAGS = -O3 -std=c++11 -Wall -Wshadow -pedantic
COMPILER = g++
FILE = $@.cpp

.PHONY: benchmark_sampler clean

benchmark_sampler:
	$(COMPILER) $@.cpp $(CXXFLAGS) -o $@.out

clean:
	rm *.out *.txt

