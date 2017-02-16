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


void Vector::set_vector(Vector& v){
	_x = v.get_x();
	_y = v.get_y();
	_z = v.get_z();
}

void Vector::invert_x(float mod){
	_x = -1 * mod * _x;
}

void Vector::invert_y(float mod){
	_y = -1 * mod * _y;
}

void Vector::invert_z(float mod){
	_z = -1 * mod * _z;
}

// Printing elements
// Virtual
void Vector::printos(std::ostream& os) const {
	os << "x:" <<_x << " y:" << _y << " z:" << _z;
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

void Particle::set_elasticity(float el){
	_elasticity = el;
}

void Particle::set_size(float sz){
	_size = sz;
}

void Particle::set_coordinates(float x, float y, float z){
	_position.set_carthesian(x,y,z);
}

void Particle::set_coordinates(float * pos){
	_position.set_carthesian(pos[0],pos[1],pos[2]);
};

void Particle::set_coordinates(Vector& pos){
	_position.set_vector(pos);
};

void Particle::set_velocity(float * v){
	_velocity.set_carthesian(v[0],v[1],v[2]);
};

void Particle::set_velocity(Vector& v){
	_velocity.set_vector(v);
};

// Getting Data
float Particle::get_mass(void) const{
	return _mass;
};

float Particle::get_elasticity(void) const{
	return _elasticity;
}

float Particle::get_size(void) const{
	return _size;
}

const Vector * Particle::position(void){
	return &_position;
}

const Vector * Particle::velocity(void){
	return &_velocity;
}

// Physics methods

void Particle::v_step(float delta_t){
	_position.set_x(_position.get_x() + _velocity.get_x() * delta_t);
	_position.set_y(_position.get_y() + _velocity.get_y() * delta_t);
	_position.set_z(_position.get_z() + _velocity.get_z() * delta_t);
};

void Particle::a_step(Vector a, float delta_t){
	_velocity.set_x(_velocity.get_x() + a.get_x() * delta_t);
	_velocity.set_y(_velocity.get_y() + a.get_y() * delta_t);
	_velocity.set_z(_velocity.get_z() + a.get_z() * delta_t);
};

void Particle::f_step(Vector f, float delta_t){
	if (_mass != 0){
		float tmp = delta_t / _mass;
		_velocity.set_x(_velocity.get_x() + f.get_x() * tmp);
		_velocity.set_y(_velocity.get_y() + f.get_y() * tmp);
		_velocity.set_z(_velocity.get_z() + f.get_z() * tmp);
	}
};

//check collision
void Particle::collision_check(const unsigned int (& gridsize)[3]){
	// Add check for change in v!!! (need to store last a nd f?) maybe add in a_step calc?.
	// check for borders
	if (_position.get_x() - _size <= 0){
		_position.set_x(_size + _elasticity*(_size - _position.get_x()));
		_velocity.invert_x(_elasticity);
	}else if(_position.get_x() + _size >= gridsize[0]){
		// do not choose 2*gridsize-pos_x in case it is too close to unsigned int
		_position.set_x( float(gridsize[0]) - _size - _elasticity*(_size - float(gridsize[0]) + _position.get_x()));
		_velocity.invert_x(_elasticity);
	}

	if (_position.get_y() - _size <= 0){
		_position.set_y(_size + _elasticity*(_size - _position.get_y()));
		_velocity.invert_y(_elasticity);
	}else if(_position.get_y() + _size >= gridsize[1]){
		// do not choose 2*gridsize-pos_x in case it is too close to unsigned int
		_position.set_y( float(gridsize[1]) - _size - _elasticity*(_size - float(gridsize[1]) + _position.get_y()));
		_velocity.invert_y(_elasticity);
	}

	if (_position.get_z() - _size <= 0){
		_position.set_z(_size + _elasticity*(_size - _position.get_z()));
		_velocity.invert_z(_elasticity);
	}else if(_position.get_z() + _size >= gridsize[2]){
		// do not choose 2*gridsize-pos_x in case it is too close to unsigned int
		_position.set_z( float(gridsize[2]) - _size - _elasticity*(_size - float(gridsize[2]) + _position.get_z()));
		_velocity.invert_z(_elasticity);
	}
};


// Update Grid
void Particle::update_gridposition(const unsigned int (& gridsize)[3]){
	collision_check(gridsize);
	_gridposition[0] = round( _position.get_x() );
	_gridposition[1] = round( _position.get_y() );
	_gridposition[2] = round( _position.get_z() );
};


// Printing elements
// Virtual
void Particle::printos(std::ostream& os) const {
	os << _gridposition[0] << ' ' << _gridposition[1] << ' ' << _gridposition[2];
};

std::ostream& operator << (std::ostream& os, const Particle& that){
	that.printos(os);
	return os;
};

// Destructor
Particle::~Particle(){

};


////////////////////////////////// End of Particle
