#include "MosqueSquare.h"


MosqueSquare::MosqueSquare() {}

void MosqueSquare::setTextures(const map<string, int>& tex) {
    mosque.setTexture(tex);
}

void MosqueSquare::drawSquare(float x, float y, float z, float length,int demoAlshek, int soor,int stone1) {
    
    MosqueGround ground(x,y,z,length,demoAlshek);
    //drowGround(x, y, z, length);


    almawazin[0] = Almawazin(x, y + 195, z - 975, length * 0.03, length, soor);
    almawazin[1] = Almawazin (x, y + 195, z + 975, length * 0.03, length, soor);

    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glTranslated(-250, 195, 930);
    almawazin[2] =  Almawazin(x - (length * 0.216), y, z - (length * 2.3), length * 0.03, length, soor);
    glPushMatrix();
    glTranslated(0, 0, 4000);
    almawazin[3] =  Almawazin(x - (length * 0.216), y, z - (length * 4.34), length * 0.03, length, soor);
    glPopMatrix();
    glPopMatrix();


    // draw stair   
    glPushMatrix();
    glTranslated(-75, -155, -1235);
    stairs[0] = Stair(x, y, z, 100, 0, 0, 30, stone1);
    //wall
    glPushMatrix();
    glTranslated(350, 0, 200);
    wall.innerWall(x, y, z, 720, stone1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-725, 0, 200);
    wall.innerWall(x, y, z, 490, stone1);
    glPopMatrix();

    glPopMatrix();
    //=======================================
    glPushMatrix();
    glRotated(180, 0, 1, 0);
    glTranslated(160, -155, -2060);
    stairs[1] =  Stair(x, y, z, 100, 0, 0, 30, stone1);

    //Left Wall 
    glPushMatrix();
    glTranslated(350, 0, 205);
    wall.innerWall(x, y, z, 500, stone1);
    glPopMatrix();
    //Right Wall
    glPushMatrix();
    glTranslated(-970, 0, 227);
    wall.innerWall(x, y, z, 745, stone1);
    glPopMatrix();

    glPopMatrix();

    //=======================================
    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glTranslated(-540, -155, -1650);
    stairs[2] =  Stair(x, y, z, 100, 0, 0, 30, stone1);

    //Left Wall 
    glPushMatrix();
    glTranslated(350, 0, 205);
    wall.innerWall(x, y, z, 811, stone1);
    glPopMatrix();

    //Right Wall
    glPushMatrix();
    glTranslated(-670, 0, 227);
    wall.innerWall(x, y, z, 440, stone1);
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glRotated(-90, 0, 1, 0);
    glTranslated(625, -155, -1650);
    stairs[3] = Stair(x, y, z, 100, 0, 0, 30, stone1);

    //Left Wall
    glPushMatrix();
    glTranslated(350, 0, 205);
    wall.innerWall(x, y, z, 440, stone1);
    glPopMatrix();
    //Right Wall
    glPushMatrix();
    glTranslated(-1040, 0, 227);
    wall.innerWall(x, y, z, 820, stone1);
    glPopMatrix();
    glPopMatrix();
    // The Dome Of The Rock
    glPushMatrix();
    glTranslated(0, 0, 1000);
    mosque.drawBodyDomeoftheRock(10, -110, 20, 20);
    glPopMatrix();
}