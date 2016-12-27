#include "particlegrid.hpp"

////////////////////////////////// Begin of Vector

// Getting Data
float Vector::get_x(void) const{
	return _x;
}

float Vector::get_y(void) const{
	return _y;
}

float Vector::get_z(void) const{
	return _z;
}

float * Vector::get_xyz(void) const{
	float ret[3] = {_x,_y,_z};
	return ret;
}

//Setting Data
void Vector::set_carthesian(float x, float y, float z){
	_x = x;
	_y = y;
	_z = z;
}

void Vector::set_spherical(float r, float phi, float theta){
	_x = r * cos(phi) * sin(theta);
	_y = r * sin(phi) * sin(theta);
	_z = r * cos(theta);
}

void Vector::set_x(float x){
	_x = x;
};

void Vector::set_y(float y){
	_y = y;
};

void Vector::set_z(float z){
	_z = z;
};

// Printing elements
// Virtual
void Vector::printos(std::ostream& os) const {
	os << _x << _y << _z;
};

std::ostream& operator << (std::ostream& os, const Vector& that){
	that.printos(os);
	return os;
};

// Destructor
Vector::~Vector(){

};

////////////////////////////////// End of Vector

////////////////////////////////// Begin of Particle

// Setting Data
void Particle::set_mass(float m){
	_mass = m;
};

void Particle::set_coordinates(float * pos){
	_position.set_carthesian(pos[0],pos[1],pos[2]);
};

void Particle::set_velocity(float * v){
	_velocity.set_carthesian(v[0],v[1],v[2]);
};

// Getting Data
float Particle::get_mass(void) const{
	return _mass;
};

float * Particle::get_position(void) const{
	return _position.get_xyz();
};

float * Particle::get_velocity(void) const{
	return _velocity.get_xyz();
};

// Physics methods

void Particle::v_step(float delta_t){

};

void Particle::a_step(Vector a, float delta_t){

};

// Printing elements
void Particle::printos(std::ostream& os) const {
	os << _position << " " << _velocity << " " << _mass;
};

std::ostream& operator << (std::ostream& os, const Particle& that){
	that.printos(os);
	return os;
};

// Destructor
Particle::~Particle(){

};


////////////////////////////////// End of Particle
