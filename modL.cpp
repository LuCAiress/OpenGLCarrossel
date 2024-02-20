#include "modL.h"
#include<vector>
#include<GL/gl.h>

vt1 modL::getVertice(std::string s){
	float x, y, z;
	sscanf(s.c_str(), "v %f %f %f", &x, &y, &z);
	vt1 result(x, y, z);	
	return result;
}

vt1 modL::getNormal(std::string s){
	float x, y, z;
	sscanf(s.c_str(), "vn %f %f %f", &x, &y, &z);
	vt1 result(x, y, z);
	return result;
}

face modL::getFace(Polygon type_, std::string s){
	int v1, v2, v3, v4, vt, n1, n2, n3, n4;

	if (type_ == Polygon::TRIANG) {
		v4 = -1; n4 = -1;
		sscanf(s.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", 
		&v1, &vt, &n1, &v2, &vt, &n2, &v3, &vt, &n3);
	}
	
	face result(type_, v1, v2, v3, v4, n1, n2, n3, n4);
	return result;
}

void modL::loadModel(unsigned & id, const char * filePath){
	std::vector<vt1> vertices;
	std::vector<vt1> normals;
	std::vector<vt1> texture;
	std::vector<face> faces;
	std::fstream arq(filePath);
	std::string line = "";

	if (!arq.is_open()) 
		std::cout << "Arquivo não encontrado! " << filePath << "\n";

	while (getline(arq, line)) {
		if (line.find("v ") != std::string::npos) {
			vt1 tempVertice = getVertice(line);
			vertices.push_back(tempVertice);
		}
		else if (line.find("vn ") != std::string::npos) {
			vt1 tempNormal = getNormal(line);
			normals.push_back(tempNormal);
		}
		//else if (line.find("vt ") != std::string::npos){
		//	vt1 tempTexture = getTexture(line);
		//	texture.push_back(tempTexture);
		//}
		else if (line.find("f ") != std::string::npos) {
			short nSpace = 0;
			for (char c : line)
				if (c == ' ') nSpace++;
			Polygon type_ = (Polygon)nSpace;
			face tempFace = getFace(type_,line);
			faces.push_back(tempFace);
		}
	}
	id = glGenLists(1);

	glNewList(id, GL_COMPILE);
	glPolygonMode(GL_FRONT, GL_FILL);
	for (int i = 0; i < faces.size(); i++) {
		int v1 = faces[i].vertice[0] - 1; 
		int v2 = faces[i].vertice[1] - 1;
		int v3 = faces[i].vertice[2] - 1; 
		int v4 = faces[i].vertice[3] - 1;
		int n1 = faces[i].normal[0] - 1;  
		int n2 = faces[i].normal[1] - 1;
		int n3 = faces[i].normal[2] - 1;  
		int n4 = faces[i].normal[3] - 1;
		if (faces[i].type == Polygon::TRIANG) {
			glBegin(GL_TRIANGLES);
			glNormal3fv(&normals[n1].x); 
			glVertex3fv(&vertices[v1].x);
			glNormal3fv(&normals[n2].x); 
			glVertex3fv(&vertices[v2].x);
			glNormal3fv(&normals[n3].x); 
			glVertex3fv(&vertices[v3].x);
			glEnd();
		}
		
	}
	glEndList();
}

