#--------------------------------------------------------------------------#
# Name: Jan Koziol                                                         #
# Email: jankoziol@gmx.de                                                  #
# GitHub: https://github.com/Jankoziol/discrete-sample                     #
#--------------------------------------------------------------------------#

CXXFLAGS = -O0 -std=c++11 -Wall -Wshadow -pedantic
COMPILER = g++
FILE = $@.cpp

.PHONY: demo_cumulative_sampler demo_walker_sampler clean

demo_cumulative_sampler:
	$(COMPILER) $@.cpp $(CXXFLAGS) -o $@.out

demo_walker_sampler:
	$(COMPILER) $@.cpp $(CXXFLAGS) -o $@.out

clean:
	rm *.out

