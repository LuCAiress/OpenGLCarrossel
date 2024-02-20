#pragma once
#include<cmath>
#include<iostream>

struct vt1 {
	float x, y, z;
	vt1();
	vt1(float x_, float y_, float z_);
	vt1 operator+(const vt1& v)const;
	vt1 operator-(const vt1& v)const;
	vt1 operator*(float k)const;
	float mag();
	void nVet();
	vt1 pV(vt1 v);
	void print();
};


struct vt2 {
	float x, y;
	vt2() :x(0.0), y(0.0) {}
	vt2(float x_, float y_) :x(x_), y(y_) {}
};