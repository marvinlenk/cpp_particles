#include <iostream>
#include <fstream>
#include "particlegrid.hpp"

int main(){
	std::cout.precision(std::numeric_limits<float>::digits10);

	const unsigned int gridsize[3] = {1e3,1e3,1e3};
	std::ofstream outputFile("grid.txt",std::ios::trunc);
	Vector x(5e2,5e2,5e2), v(0,0,0), a(0,0,-9.81);
	Particle part(x,v,10,0.9);
	std::cout << part << std::endl;
	//float delta_t = 1e-2 + 1e-10; //whatthefuck?
	float delta_t = 1.0/30;

	int i,j;
	for(i = 0; i < 3e2; i++){
		outputFile << i << ' ' << part << std::endl;
		for(j = 0; j < 1e1; j++){
			part.a_step(a,delta_t);
			part.update_gridposition(gridsize);
		}
	}
	outputFile << i << ' ' << part << std::endl;
	outputFile.close();
}
