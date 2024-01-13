#ifndef Qmosque_H
#define Qmosque_H
#include <Windows.h>
#include <winreg.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <math.h>
#include <GLAUX.H>
#include "Model_3DS.h"
#include <vector>
#include <mmsystem.h>
#pragma comment(lib, "AdvAPI32.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")
#pragma comment(lib, "winmm.lib")
using namespace std;
class Qmosque 
{
	public:
	
	#define PI 3.14159265358979323846
		GLuint DOORS, MAINBLOCK, carpet, MAINUP;
		GLuint ROOF2UP, ROOF2DOWN;
		GLuint mainroof, subroof, specialroof, roof, sideroof;
		GLuint inside;
		GLuint cylinder1, cylinder2, cylinder3, cuboid1, cuboid2, cuboid3;
		GLuint fence, pedestal, pedestal2, extension;
		GLuint window1, window2, window3;
		GLuint sidedoor_o, sidedoor_i;
		GLuint emam , glass;
		
	Qmosque();
	void drawTexturedCuboid(GLuint texture, float width, float height, float depth, float xpos, float ypos, float zpos, float s, float t);


	void drawcylinder(GLuint texture, int numSegments, float radius, float height);


	void drawHcube(GLuint texture, float height, float width, float depth, float r, int numofsegments, float x, float y, float z, float s, float t);

	void drawBArc(float x, float y, float z, float r, float p, float st, GLuint tex);


	void drawArc(float x, float y, float z, float r, float l, float p, float st, GLuint tex);

	void drawBlockArc(GLuint texture, float radius, float startAngle, float endAngle, int segments, float blockWidth, float blockHeight, float blockDepth);

	void Rect(GLuint texture, float minX, float maxX, float minY, float maxY, float minZ, float maxZ, float s, float t);

	void drawdome(float a, float b, float c, float radius, int tex, int tex1, int sizeofbase);
	void drawpolygon(float x, float y, float z, float radius, float length, int numVertices, int tex);
	void qmosque();

};

#endif