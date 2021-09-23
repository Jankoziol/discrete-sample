//------------------------------------------------------------------------//
// Name: Jan Koziol                                                       //
// Email: jankoziol@gmx.de                                                //
// GitHub: https://github.com/Jankoziol/discrete-sample                   //
//------------------------------------------------------------------------//

#pragma once

#include <vector>
#include <numeric>
#include <cstdint>
#include <stdexcept>



class walker_sampler {
	
	private :
		std::vector<double> prob;
		std::vector<int> inx; 
	
	public :
		walker_sampler (  );
		walker_sampler ( const std::vector<double> & w ); 
		void set ( const std::vector<double> & w );
		void set (  );
		int draw ( const double u, const int i );
		int draw ( double u ); // This is dirty, here no const possible

};



walker_sampler::walker_sampler (  ) {
	set (  );
}

walker_sampler::walker_sampler ( const std::vector<double> & w ) {
	set ( w );
}

void walker_sampler::set ( const std::vector<double> & w ) {
	int n = w.size();
	prob = std::vector<double> ( n, 0.0 );
	inx = std::vector<int> ( n, -1 );
	double sumw = std::accumulate ( w.begin(), w.end(), 0.0 );
	bool onlyzero = true;
	for ( int i = 0; i < n; i++ ) { 
		if ( w[i] < 0 ) throw std::domain_error( "Error walker_sampler::set: Negative entries in argument w." );
		else if ( ( onlyzero ) && ( w[i] > 0 ) ) onlyzero = false;
		prob[i] = (w[i]*n)/sumw;
	}
	if ( onlyzero ) throw std::domain_error( "Error walker_sampler::set: Only zeros as entries in argument w." );
	std::vector<int> vshort;
	std::vector<int> vlong;
	for ( int i = 0; i < n; i++ ) {
		if ( prob[i] < 1 ) vshort.push_back ( i );
		if ( prob[i] > 1 ) vlong.push_back ( i );
	}
	while ( vshort.size() && vlong.size() ) {
		int j = vshort.back();
		vshort.pop_back();
    	int k = vlong.back();
		inx[j] = k;
		prob[k] -= ( 1 - prob[j] );
		if ( prob[k] < 1 ) {
    		vshort.push_back( k );
    		vlong.pop_back();
		}
	}
}

void walker_sampler::set (  ) {
	set ( {1} );
}

int walker_sampler::draw ( const double u, const int i ) {
	if ( ( u > 1 ) || ( u < 0 ) ) 
		throw std::domain_error( "Error walker_sampler::draw: Argument u is out of the required bounds [0,1]." );
	if ( ( i < 0) || ( (unsigned)i >= inx.size() ) )
		throw std::domain_error( "Error walker_sampler::draw: Argument i is out of the required bounds." );
	if ( u <= prob[i] ) return i;
	return inx[i];
}

int walker_sampler::draw ( double u ) {
	if ( ( u > 1 ) || ( u < 0 ) ) 
		throw std::domain_error( "Error walker_sampler::draw: Argument u is out of the required bounds [0,1]." );
	int64_t i = ( ( reinterpret_cast<int64_t&>(u) & (((int64_t)1 << 53) - 1) ) % inx.size() );
	return draw ( u, i );
}
