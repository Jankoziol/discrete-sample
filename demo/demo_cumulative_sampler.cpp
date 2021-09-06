//------------------------------------------------------------------------//
// Name: Jan Koziol                                                       //
// Email: jankoziol@gmx.de                                                //
// GitHub: https://github.com/Jankoziol/discrete-sample                   //
//------------------------------------------------------------------------//



#include "../source/cumulative_sampler.hpp"

#include <vector>
#include <random>
#include <iostream>
#include <string>
#include <stdexcept>



void first_demo (  ) {

	// For the cumulative_sampler it does not matter if we define the 
	// weights for a given index as relative weights or probabilities.
	// We define the weight to draw an integer i, by setting the value
	// in an std::vector<double> at index i to the desired weight.
	std::vector<double> w = {1,2,3,0,5};

	// We can now constuct the cumulative_sampler object.
	cumulative_sampler cs ( w );

	// To draw from the discrete probability distribution we need
	// doubles drawn from the uniform real distribution from 0 to 1
	std::mt19937 gen ( 0 ); // Standard mersenne twister engine with seed 0
    std::uniform_real_distribution<double> dis ( 0.0, 1.0 );	

	// To draw a random number from the discrete probability distribution
	// we call the draw method of the cumulative_sampler with a random 
	// number drawn from the real distribution dis as an argument
	int d = cs.draw ( dis ( gen ) );

	// To convince ourselves that the outputs of the cumulative_sampler's
	// draw method are given by the weights provided by the vector w,
	// we can now create a histogram of 100000 draws and compare it with
	// the original distribution.
	std::vector<int> hist = {0,0,0,0,0};
	for ( int i = 0; i < 100000; i++ ) {
		int di = cs.draw ( dis ( gen ) );
		hist[ di ] = hist [ di ] + 1;
	}

	// Note that the mersenne twister engine is seeded with 0, therefore 
	// the execution of the code will always lead to the same .	
	std::cout << "\nfirst_demo:" << std::endl;
	std::string o = "We initialized a cumulative_sampler class ";
	o += "with the weight vector {1,2,3,0,5}.\n";
	o += "The probabilities are therefore {0.091,0.182,0.273,0.000,0.454}.";
	o += "\nThe first random number we drew was d = ";
	o += std::to_string ( d );
	o += "\nThe histogram we produced reflects the distribution:\n{";
	for ( auto & e: hist) o += std::to_string ( e/100000.0 ) + ",";
	o = o.substr ( 0 , o.length (  ) - 1 ) + "}\n";
	std::cout << o << std::endl;

}

void second_demo (  ) {

	// We can also construct the cumulative_sampler with no weights given.
	// In this case the cumulative_sampler always draws the zero.
	cumulative_sampler cs = cumulative_sampler (  );
	std::mt19937 gen ( 0 ); // Standard mersenne twister engine with seed 0
    std::uniform_real_distribution<double> dis ( 0.0, 1.0 );	
	int d = cs.draw ( dis ( gen ) );
	
	// Note that the mersenne twister engine is seeded with 0, therefore 
	// the execution of the code will always lead to the same .	
	std::string o = "\nsecond_demo:";
	o += "\nIf no weights are given at the construction ";
	o += "the cumulative_sampler always returns the result ";
	o += std::to_string ( d ) + ".\n";
	std::cout << o << std::endl;

}

void third_demo (  ) {
	
	// The weights of a cumulative_sampler can be set or reset by the
	// set method. 
	cumulative_sampler cs = cumulative_sampler (  );
	std::vector<double> w = {0,2,3,1,5};
	std::mt19937 gen ( 0 ); // Standard mersenne twister engine with seed 0
    std::uniform_real_distribution<double> dis ( 0.0, 1.0 );	
	int d1 = cs.draw ( dis ( gen ) );
	cs.set ( w );
	int d2 = cs.draw ( dis ( gen ) );
	cs.set (  );
	int d3 = cs.draw ( dis ( gen ) );

	// Note that the mersenne twister engine is seeded with 0, therefore 
	// the execution of the code will always lead to the same .	
	std::cout << "\nthird_demo:" << std::endl;
	std::string o = "A cumulative_sampler constructed without weights ";
	o += "always gives " + std::to_string ( d1 ) + " as a result.";
	o += " Setting the weight to {0,2,3,1,5} gives then for example ";
	o += std::to_string ( d2 ) + ". Setting without any weight then again ";
	o += "results in a sampler that always gives ";
	o += std::to_string ( d1 ) + " as a result.\n";
	std::cout << o << std::endl;
	
}

void fourth_demo (  ) {
	
	std::cout << "\nfourth_demo:" << std::endl;
	// There are some exceptions implemented in the cumulative_sampler.
	// The most important one is that the code realises when negative
	// weights occur.
	std::vector<double> w1 = {-1,2,3,1,5};
	try {
		cumulative_sampler cs ( w1 );
	}
	catch (std::exception & ex) {
		std::cout << "Not allowed are " << ex.what() << "." << std::endl;
	}
	
	// The code also checks if there are only zeros as weights provided.
	std::vector<double> w2 = {0,0,0,0,0};
	try {
		cumulative_sampler cs ( w2 );
	}
	catch (std::exception & ex) {
		std::cout << "Not allowed are " << ex.what() << "." << std::endl;
	}

	// The code also checks if the argument of draw is element of [0,1] .
	std::vector<double> w = {1,2,3,1,5};
	cumulative_sampler cs ( w );
	try { 
		cs.draw(2.0);
	}
	catch (std::exception & ex) {
		std::cout << "Not allowed if " << ex.what() << ".\n" << std::endl;
	}

}


int main (  ) {
	first_demo (  );
	second_demo (  );
	third_demo (  );
	fourth_demo (  );
}
