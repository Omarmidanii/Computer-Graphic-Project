#ifndef Wall_H
#define Wall_H
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


class Wall {

public:
	Wall();
	void innerWall(float x, float y, float z, float lengthX,int stone1);
	void outerWall(float centerX, float centerY, float centerZ, float cubeSize, float wallLength, float wallWidth, int tex, int roof);
	void drawgCubic(float x, float y, float z, float lengthx, float lengthy, float lengthz,int roof, int wallout);

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