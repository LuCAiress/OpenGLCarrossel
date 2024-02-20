#include "v1.h"

	vt1::vt1() :x(0.0), y(0.0), z(0.0) {}
	vt1::vt1(float x_, float y_, float z_) :x(x_), y(y_), z(z_) {}
	
	vt1 vt1::operator+(const vt1& v)const{ 
		return vt1(x + v.x, y + v.y, z + v.z); 
	}

	vt1 vt1::operator-(const vt1 & v) const{
		return vt1(x - v.x, y - v.y, z - v.z);
	}
	
	vt1 vt1::operator*(float k)const { 
		return vt1(x*k, y*k, z*k); 
	}
	
	float vt1::mag() { 
		return sqrt(x*x + y * y + z * z);
	}

	void vt1::nVet() {
		float m = mag();
		x = x / m; 
		y = y / m; 
		z = z / m;
	}

	vt1 vt1::pV(vt1 v) {
		return vt1(
			y*v.z - z * v.y, 
			z*v.x - x * v.z, 
			x*v.y - y * v.x);
	}

	void vt1::print(){
		std::cout << "(" << x << "," << y << "," << z << ")";
	}

