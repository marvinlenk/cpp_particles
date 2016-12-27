#ifndef PARTICLEGRID_HPP_
#define PARTICLEGRID_HPP_
#include <iostream>
#include <cmath>
#endif /* PARTICLEGRID_HPP_ */

class Vector{
private:
	float _x,_y,_z;

public:
	Vector(float x=0, float y=0, float z=0):_x(x),_y(y),_z(z){};

	void set_carthesian(float,float,float);
	void set_spherical(float,float,float);
	void set_x(float);
	void set_y(float);
	void set_z(float);

	float get_x(void)const;
	float get_y(void)const;
	float get_z(void)const;
	float * get_xyz(void) const;

	virtual void printos(std::ostream& os) const;
	friend std::ostream& operator<< (std::ostream & os, const Vector & that);

	virtual ~Vector();
};

class Particle{
private:
	float _mass; //in kilograms
	Vector _position;
	Vector _velocity;
public:
	Particle(float*,float*,float);

	void set_mass(float);
	void set_coordinates(float*);
	void set_velocity(float*);

	float get_mass(void) const;
	float * get_position(void) const;
	float * get_velocity(void) const;

	// physics methods
	void v_step(float);
	void a_step(Vector,float);

	virtual void printos(std::ostream& os) const;
	friend std::ostream& operator<< (std::ostream & os, const Particle & that);

	virtual ~Particle();
};
