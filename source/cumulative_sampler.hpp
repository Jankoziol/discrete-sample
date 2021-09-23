//------------------------------------------------------------------------//
// Name: Jan Koziol                                                       //
// Email: jankoziol@gmx.de                                                //
// GitHub: https://github.com/Jankoziol/discrete-sample                   //
//------------------------------------------------------------------------//

#pragma once

#include <vector>
#include <numeric>
#include <stdexcept>
#include <iostream>



class cumulative_sampler {

	protected :
		std::vector<double> cp; // cp - cumulative probabilities
	
	public : 
		cumulative_sampler (  );
		cumulative_sampler ( const std::vector<double> & w );
		void set (  );
		void set ( const std::vector<double> & w );
		int draw ( const double u );

};



cumulative_sampler::cumulative_sampler (  ) {
	set (  );
}

cumulative_sampler::cumulative_sampler ( const std::vector<double> & w ) {
	set ( w );
}

void cumulative_sampler::set (const std::vector<double> & w) {
	cp = {0};
	cp.reserve ( w.size()+1 );
	bool onlyzero = true;
	for ( auto & e : w ) {
		if ( e < 0 ) throw std::domain_error( "Error cumulative_sampler::set: Negative entries in argument w." );
		else if ( ( onlyzero ) && ( e > 0 ) ) onlyzero = false;
		cp.push_back ( cp.back() + e );
	}
	if ( onlyzero ) throw std::domain_error( "Error cumulative_sampler::set: Only zeros as entries in argument w." );
	cp.erase ( cp.begin() );
	for ( auto & e : cp ) e = e/cp.back();
}

void cumulative_sampler::set (  ) {
	set ( {1} );
}

int cumulative_sampler::draw ( const double u ) {
	if ( ( u > 1 ) || ( u < 0 ) ) 
			throw std::domain_error( "Error cumulative_sampler::draw: Argument u is out of the required bounds [0,1]." );
	int k = 0;
	while ( u > cp[k] ) k++;
	return k;
}
