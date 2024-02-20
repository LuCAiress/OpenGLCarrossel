#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include"v1.h"

enum Polygon{TRIANG=3, QUAD=4};

struct face {
	Polygon type;
	int vertice[4];
	int normal[4];
	face(Polygon type_, 
		int v1, int v2, int v3, int v4,
		int n1, int n2, int n3, int n4) {
		vertice[0] = v1; 
		vertice[1] = v2;
		vertice[2] = v3; 
		vertice[3] = v4;
		normal[0] = n1; 
		normal[1] = n2;
	   	normal[2] = n3; 
		normal[3] = n4;
		type = type_;
	}
};

namespace modL{
	vt1 getVertice(std::string s);
	vt1 getNormal(std::string s);
	vt1 getTexture(std::string s);
	face getFace(Polygon type_, std::string s);
	void loadModel(unsigned& id, const char* filePath);
};

