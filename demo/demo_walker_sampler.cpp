//------------------------------------------------------------------------//
// Name: Jan Koziol                                                       //
// Email: jankoziol@gmx.de                                                //
// GitHub: https://github.com/Jankoziol/discrete-sample                   //
//------------------------------------------------------------------------//



#include "../source/walker_sampler.hpp"

#include <vector>
#include <random>
#include <iostream>
#include <string>
#include <stdexcept>



void first_demo (  ) {

	// For the walker_sampler it does not matter if we define the 
	// weights for a given index as relative weights or probabilities.
	// We define the weight to draw an integer i, by setting the value
	// in an std::vector<double> at index i to the desired weight.
	const std::vector<double> w = {1,2,3,0,5};

	// We can now constuct the walker_sampler instance.
	walker_sampler ws ( w );

	// To draw from the discrete probability distribution we need
	// doubles drawn from the uniform real distribution from 0 to 1 and
	// integers drawn from a uniform integer distribution from w.size()-1.
	std::mt19937 gen ( 0 ); // Standard mersenne twister engine with seed 0
	std::uniform_real_distribution<double> dis ( 0.0, 1.0 );	
	std::uniform_int_distribution<int> idis ( 0, w.size()-1 );	

	// To draw a random number from the discrete probability distribution
	// we call the draw method of the walker_sampler with a random 
	// number drawn from the real distribution dis as an argument and 
	// a random integer drawn from idis.
	int d = ws.draw ( dis ( gen ), idis ( gen ) );

	// To convince ourselves that the outputs of the walker_sampler's
	// draw method are given by the weights provided by the vector w,
	// we can now create a histogram of 100000 draws and compare it with
	// the original distribution.
	std::vector<int> hist = {0,0,0,0,0};
	for ( int i = 0; i < 100000; i++ ) {
		int di = ws.draw ( dis ( gen ), idis ( gen ) );
		hist[ di ] = hist [ di ] + 1;
	}

	// Note that the mersenne twister engine is seeded with 0, therefore 
	// the execution of the code will always lead to the same .	
	std::cout << "\nfirst_demo:" << std::endl;
	std::string o = "We initialized a walker class ";
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

	// The difference to the first demo is that we use the dirty draw
	// method where only one double is needed and the required integer
	// is derived from the significants.
	// WARNING: This is not 100% safe ...
	// As before for the walker_sampler it does not matter if we define the 
	// weights for a given index as relative weights or probabilities.
	// We define the weight to draw an integer i, by setting the value
	// in an std::vector<double> at index i to the desired weight.
	const std::vector<double> w = {1,2,3,0,5};

	// We can now constuct the walker_sampler instance.
	walker_sampler ws ( w );

	// To draw from the discrete probability distribution we need
	// doubles drawn from the uniform real distribution from 0 to 1. Here
	// we explicitly do not need any random integers.
	std::mt19937 gen ( 0 ); // Standard mersenne twister engine with seed 0
	std::uniform_real_distribution<double> dis ( 0.0, 1.0 );	

	// To draw a random number from the discrete probability distribution
	// we call the draw method of the walker_sampler with a random 
	// number drawn from the real distribution dis as an argument.
	// Again keep in mind we do not need any integers
	int d = ws.draw ( dis ( gen ) );

	// To convince ourselves that the outputs of the walker_sampler's
	// draw method are given by the weights provided by the vector w,
	// we can now create a histogram of 100000 draws and compare it with
	// the original distribution.
	std::vector<int> hist = {0,0,0,0,0};
	for ( int i = 0; i < 100000; i++ ) {
		int di = ws.draw ( dis ( gen ) );
		hist[ di ] = hist [ di ] + 1;
	}

	// Note that the mersenne twister engine is seeded with 0, therefore 
	// the execution of the code will always lead to the same .	
	std::cout << "\nsecond_demo:" << std::endl;
	std::string o = "We initialized a walker class ";
	o += "with the weight vector {1,2,3,0,5}.\n";
	o += "The probabilities are therefore {0.091,0.182,0.273,0.000,0.454}.";
	o += "\nThe first random number we drew was d = ";
	o += std::to_string ( d );
	o += "\nThe histogram we produced reflects the distribution:\n{";
	for ( auto & e: hist) o += std::to_string ( e/100000.0 ) + ",";
	o = o.substr ( 0 , o.length (  ) - 1 ) + "}\n";
	std::cout << o << std::endl;

}

void third_demo (  ) {

	// We can also construct the walker_sampler with no weights given.
	// In this case the walker_sampler always draws the zero.
	walker_sampler ws = walker_sampler (  );
	std::mt19937 gen ( 0 ); // Standard mersenne twister engine with seed 0
    std::uniform_real_distribution<double> dis ( 0.0, 1.0 );	
	int d = ws.draw ( dis ( gen ), 0 );
	int c = ws.draw ( dis ( gen ) );

	if ( ! ( d == c ) ) 
		std::cout << "draw methods give differet result" << std::endl;
	
	// Note that the mersenne twister engine is seeded with 0, therefore 
	// the execution of the code will always lead to the same output.	
	std::string o = "\nthird_demo:";
	o += "\nIf no weights are given at the construction ";
	o += "the walker_sampler always returns the result ";
	o += std::to_string ( d ) + ".\n";
	std::cout << o << std::endl;

}

void fourth_demo (  ) {
	
	// The weights of a walker_sampler can be set or reset by the
	// set method. 
	walker_sampler ws = walker_sampler (  );
	const std::vector<double> w = {0,2,3,1,5};
	std::mt19937 gen ( 0 ); // Standard mersenne twister engine with seed 0
    std::uniform_real_distribution<double> dis ( 0.0, 1.0 );	
	std::uniform_int_distribution<int> idis ( 0, 4 );	
	int d1 = ws.draw ( dis ( gen ), 0 );
	ws.set ( w );
	int d2 = ws.draw ( dis ( gen ), idis ( gen ) );
	ws.set (  );
	int d3 = ws.draw ( dis ( gen ) );

	// Note that the mersenne twister engine is seeded with 0, therefore 
	// the execution of the code will always lead to the same output.	
	std::cout << "\nfourth_demo:" << std::endl;
	std::string o = "A walker_sampler constructed without weights ";
	o += "always gives " + std::to_string ( d1 ) + " as a result.";
	o += " Setting the weight to {0,2,3,1,5} gives then for example ";
	o += std::to_string ( d2 ) + ". Setting without any weight then again ";
	o += "results in a sampler that always gives ";
	o += std::to_string ( d3 ) + " as a result.\n";
	std::cout << o << std::endl;
	
}

void fifth_demo (  ) {
	
	std::cout << "\nfifth_demo:" << std::endl;
	// There are some exceptions implemented in the walker_sampler.
	// The most important one is that the code realises when negative
	// weights occur.
	const std::vector<double> w1 = {-1,2,3,1,5};
	try {
		walker_sampler ws ( w1 );
	}
	catch (std::exception & ex) {
		std::cout << ex.what() << std::endl;
	}
	
	// The code also checks if there are only zeros as weights provided.
	const std::vector<double> w2 = {0,0,0,0,0};
	try {
		walker_sampler ws ( w2 );
	}
	catch (std::exception & ex) {
		std::cout << ex.what() << std::endl;
	}

	// The code also checks if the argument of draw is element of [0,1] .
	const std::vector<double> w = {1,2,3,1,5};
	walker_sampler ws ( w );
	try { 
		ws.draw(2.0);
	}
	catch (std::exception & ex) {
		std::cout << ex.what() << std::endl;
	}

	// The code also checks if the integer argument of draw.
	try { 
		ws.draw(0.8, 7);
	}
	catch (std::exception & ex) {
		std::cout << ex.what() << "\n" << std::endl;
	}

}



int main (  ) {
	first_demo (  );
	second_demo (  );
	third_demo (  );
	fourth_demo (  );
	fifth_demo (  );
}
