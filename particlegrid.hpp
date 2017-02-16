#ifndef PARTICLEGRID_HPP_
#define PARTICLEGRID_HPP_
#include <iostream>
#include <fstream>
#include <cmath>
#endif /* PARTICLEGRID_HPP_ */

class Vector{
private:
	float _x,_y,_z;

public:
	// directly plug it in
	Vector(float x=0, float y=0, float z=0):_x(x),_y(y),_z(z){};
	// copy from vector
	Vector(Vector& v):_x(v.get_x()),_y(v.get_y()),_z(v.get_z()){};

	void set_carthesian(float,float,float);
	void set_spherical(float,float,float);
	void set_x(float);
	void set_y(float);
	void set_z(float);
	void set_vector(Vector&);

	void invert_x(float = 1);
	void invert_y(float = 1);
	void invert_z(float = 1);

	float get_x(void)const;
	float get_y(void)const;
	float get_z(void)const;

	virtual void printos(std::ostream& os) const;
	friend std::ostream& operator<< (std::ostream & os, const Vector & that);

	virtual ~Vector();
};

class Particle{
private:
	float _mass; //in kilograms
	float _elasticity; // amout of velocity reduction at each wall hitting
	float _size; //size for collision checks
	Vector _position;
	unsigned int _gridposition[3];
	Vector _velocity;

	void collision_check(const unsigned int (& gridsize)[3]);

public:
	Particle(float m=0, float el=1, float sz=1):_mass(m),_elasticity(el),_size(sz),_position(),_velocity(){};
	Particle(Vector& x,Vector& v,float m=0, float el=1, float sz=1):
		_mass(m),_elasticity(el),_size(sz),_position(x),_velocity(v)
		{
			_gridposition[0] = round(x.get_x());
			_gridposition[1] = round(x.get_y());
			_gridposition[2] = round(x.get_z());
		};

	void set_mass(float);
	void set_elasticity(float);
	void set_size(float);
	void set_coordinates(float,float,float);
	void set_coordinates(float*);
	void set_coordinates(Vector&);
	void set_velocity(float*);
	void set_velocity(Vector&);


	float get_mass(void) const;
	float get_elasticity(void) const;
	float get_size(void) const;
	// not shure if this is intelligent... check if set_x is working there?
	const Vector * position(void);
	const Vector * velocity(void);

	// physics methods
	void v_step(float); // speed (normal time step)
	void a_step(Vector,float); // accelleration
	void f_step(Vector,float); // force

	// update grid
	void update_gridposition(const unsigned int (& gridsize)[3]);

	virtual void printos(std::ostream& os) const;
	friend std::ostream& operator<< (std::ostream & os, const Particle & that);

	virtual ~Particle();
};
