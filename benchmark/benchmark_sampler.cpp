//------------------------------------------------------------------------//
// Name: Jan Koziol                                                       //
// Email: jankoziol@gmx.de                                                //
// GitHub: https://github.com/Jankoziol/discrete-sample                   //
//------------------------------------------------------------------------//



#include "../source/walker_sampler.hpp"
#include "../source/cumulative_sampler.hpp"

#include <vector>
#include <random>
#include <fstream>
#include <iostream>
#include <chrono>
#include <climits>



std::vector<double> weights 
	( const int len, std::mt19937 & eng, 
	  std::uniform_real_distribution<> & dis ) 
{
	std::vector<double> returner (len, 0);
	for ( int i = 0; i < len; i++ ) returner[i] = dis(eng);
	return returner;
}

void benchmark ( int nit ) {
	std::vector<int> l = {};
	for (int i = 1; i < 100; i++) l.push_back(i);
	for (int i = 100; i < 501; i = i + 5) l.push_back(i);
	for (int i = 500; i < 1001; i = i + 20) l.push_back(i);
	std::mt19937 gen(0); 
    std::uniform_real_distribution<> dis(0.0, 1.0);
    std::uniform_real_distribution<> ddis(0.0, 10.0);
    std::uniform_int_distribution<> idis(0,INT_MAX);
	walker_sampler ws = walker_sampler (  );
	cumulative_sampler cs = cumulative_sampler (  );
	std::ofstream outfile;
  	outfile.open ("benchmark_sampler.txt");
	outfile << "configuration space size,time walker [ms]";
	outfile << ",time walker dirty [ms],time cumulative [ms]\n";
	for ( auto & e : l ) {
		std::cout << e << std::endl;
		std::vector<double> w = weights ( e, gen, ddis );
		std::vector<double> r1 ( e, 0 );
		std::vector<double> r2 ( e, 0 );
		std::vector<double> r3 ( e, 0 );
		ws.set ( w );
		cs.set ( w );
		auto t1 = std::chrono::high_resolution_clock::now();
		for ( int i = 0; i < nit; i++ ) {
			int p = ws.draw ( dis ( gen ), idis ( gen ) % e );
			r1[p] = r1[p]+1;
		}
		auto t2 = std::chrono::high_resolution_clock::now();
		for ( int i = 0; i < nit; i++ ) {
			int p = ws.draw ( dis ( gen ) );
			r2[p] = r2[p]+1;
		}
		auto t3 = std::chrono::high_resolution_clock::now();
		for ( int i = 0; i < nit; i++ ) {
			int p = cs.draw ( dis ( gen ) );
			r3[p] = r3[p]+1;
		}
		auto t4 = std::chrono::high_resolution_clock::now();
		//for (auto & elm : r1) std::cout << elm/nit << " ";
		//std::cout << std::endl;
		//for (auto & elm : r2) std::cout << elm/nit << " ";
		//std::cout << std::endl;
		//for (auto & elm : r3) std::cout << elm/nit << " ";
		//std::cout << std::endl;
		std::chrono::duration<double, std::milli> dtw = t2 - t1;
		std::chrono::duration<double, std::milli> dtwd = t3 - t2;
		std::chrono::duration<double, std::milli> dtc = t4 - t3;
		outfile << e << "," << dtw.count() << ",";
		outfile << dtwd.count() << "," << dtc.count() << "\n";
	}
  	outfile.close();
}

int main (  ) {
	benchmark ( 10000000 );
}
