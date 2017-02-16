#include <iostream>
#include <fstream>
#include "particlegrid.hpp"

int main(){
	std::cout.precision(std::numeric_limits<float>::digits10);

	const unsigned int gs = 1e3;
	int scale = 100; // how many points are one meter?
	int prec=10; // steps per frame (just precision, no fps change)
	const unsigned int gridsize[3] = {gs,gs,gs};
	std::ofstream outputFile("./grid.txt",std::ios::trunc);
	Vector x(5e2,5e2,5e2), v(0,0,0), a(0,0,-9.81*scale),f(0,scale,0);//scale now set to cm
	int i,j,k;
	int no=100,seconds=60,fps=60;
	int blocks = seconds*fps;
	Particle *part = new Particle[no];
	for(i = 0; i < no; ++i){
		part[i].set_coordinates(0 + (gs/no*(i+1.0/2)) , 250 , gs/2 + i);
		//part[i].set_coordinates(0 + (gs/no*(i+1.0/2)) , 250 , gs/2);
		part[i].set_size(10);
		part[i].set_velocity(v);
		//part[i].set_elasticity(1 - 1.0/((i+1)*5));
		//part[i].set_mass(no-i);
		part[i].update_gridposition(gridsize);
		//std::cout << part[i] << " m:" << part[i].get_mass() << " el:" << part[i].get_elasticity() << std::endl;
	}

	//float delta_t = 1e-2 + 1e-10; //whatthefuck?
	float delta_t = (1.0/fps) / prec; //for nice 30fps experience

	std::ofstream paramFile("./parameters.ini",std::ios::trunc);
	paramFile << no << std::endl;
	paramFile << blocks << std::endl;
	paramFile << delta_t << std::endl;
	paramFile << fps << std::endl;
	paramFile << gridsize[0] << std::endl;
	paramFile << gridsize[1] << std::endl;
	paramFile << gridsize[2] << std::endl;
	paramFile << scale << std::endl;
	paramFile.close();

	for(i = 0; i < blocks; i++){
		for(k = 0; k < no; k++){
			outputFile << i*delta_t*prec << ' ' << part[k] << std::endl;
		}
		for(j = 0; j < prec; j++){
			for(k = 0; k < no; k++){
				part[k].a_step(a,delta_t);
				//part[k].f_step(f,delta_t);
				part[k].v_step(delta_t);
				part[k].update_gridposition(gridsize);
			}
		}
	}
	for(k = 0; k < no; k++){
		outputFile << i*delta_t*prec << ' ' << part[k] << std::endl;
	}
	outputFile.close();
	std::cout << "Done" << std::endl;
}
