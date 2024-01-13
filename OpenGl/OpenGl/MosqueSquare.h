#ifndef Mosque_Square_H
#define Mosque_Square_H
#include "Almawazin.h"
#include "Stair.h"
#include "MosqueGround.h"
#include "Wall.h"
#include "DomeOfRock.h"



class MosqueSquare {
public:

	MosqueSquare();
	void setTextures(const map<string, int>& tex);
	void drawSquare(float x, float y, float z, float length, int demoAlshek, int soor, int stone1);
	//MosqueSquare(float x, float y, float z, float length, int demoAlshek, int soor,int stone1,);

private:
	Almawazin almawazin[4];
	Stair stairs[4];
	Wall wall;
	DomeOfTheRock mosque;

};



#endif