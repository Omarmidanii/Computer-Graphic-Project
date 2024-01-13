#ifndef Dome_of_the_Rock_H
#define Dome_of_the_Rock_H
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
#include <vector>

using namespace std;

class DomeOfTheRock
{


public:

	DomeOfTheRock();
	void setTexture(const map<string, int> &tex);
	void drawArc(float x, float y, float z, float r, float p, float st, int tex);
	void drawJamb(float x, float y, float z, float r, int tex, int number);
	void drawBArc(float x, float y, float z, float r, float p, float st, int tex);
	void buildArcDome(float x, float y, float z, float r);
	void drawoctagon(float length, int tex);
	void drawceil(float x, float y, float z, int tex);
	void drawpolygon(float x, float y, float z, float radius, float length, int numVertices, int tex);
	void drawdome(float a, float b, float c, float radius, int tex, int tex1, int sizeofbase);
	void drawBodyDomeoftheRock(float x, float y, float z, float r);



private:
	struct Point {
		float x, y;
	};

	struct Point3D {
		float x, y, z;
	};
	map<string, int> domeOfRockTex;
	vector<Point3D> v;
	const int slices = 200;  // Number of horizontal slices
	const int stacks = 100;  // Number of vertical stacks
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