#ifndef Almwazin_H
#define Almwazin_H

#include <GL/glew.h>
#include <corecrt_math.h>
#include <Windows.h>
#include <winreg.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <vector>

using namespace std;


class Almawazin {

public:
	Almawazin();
	Almawazin(float x, float y, float z, float r, float length,int soor);
	void drawArc(float x, float y, float z, float r, float p, float st, int tex);
	void drawJamb(float x, float y, float z, float r, int tex, int number);



private:
	struct Point {
		float x, y;
	};
	Point TexCoor[4] = { {0,0} , {1,0} , {1,1} , {0,1} };
	int faces[6][4] = {
	{ 0, 1, 2, 3 }, // front face
	{ 1, 5, 6, 2 }, // right face
	{ 4, 5, 6, 7 }, // back face
	{ 0, 4, 7, 3 }, // left face
	{ 3, 2, 6, 7 }, // top face
	{ 4, 5, 1, 0 }  // bottom face
	};
};

#endif