#ifndef Building_H
#define Building_H
#define M_PI 3.14159265358979323846
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
#include <map>
using namespace std;


class Building {

public:
	Building();
	void setTexture(const map<string, int>& tex);
	void drawFirstHouse(float x, float y, float z);
	void drawdome(float a, float b, float c, float radius, int tex, int tex1, int sizeofbase);
	void drawpolygon(float x, float y, float z, float radius, float length, int numVertices, int tex);
	void drawSecondHouse(float x, float y, float z);


private:
	struct Point {
		float x, y;
	};

	Point TexCoor[4] = { {0,0} , {1,0} , {1,1} , {0,1} };

	map<string, int> buildingTex;
	const int slices = 200;  // Number of horizontal slices
	const int stacks = 100;  // Number of vertical stacks
	int faces[6][4] = {
	{ 0, 1, 2, 3 }, // front face
	{ 1, 5, 6, 2 }, // right face
	{ 4, 5, 6, 7 }, // back face
	{ 0, 4, 7, 3 }, // left face
	{ 3, 2, 6, 7 }, // top face
	{ 4, 5, 1, 0 }  // bottom face
	};

	double vertices[8][3] = {
	{ -2 ,  -2  ,  +9 },  // 0
	{ +2 ,  -2  ,  +9}, // 1
	{ +2 ,  +2  ,  +9 },   // 2
	{ -2 ,  +2  ,  +9 },  // 3
	{ -2 ,  -2  ,  +12},   // 4
	{ +2 ,  -2  ,  +12 },   // 5
	{ +2 ,  +2  ,  +12 },   // 6
	{ -2 ,  +2  ,  +12 }  // 7
	};

};




#endif