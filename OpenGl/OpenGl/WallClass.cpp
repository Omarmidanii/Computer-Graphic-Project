#include "Wall.h"

Wall::Wall(){}

void Wall::innerWall(float x, float y, float z, float lengthX,int stone1) {
    for (int i = 0; i < 6; i++) {
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, stone1);

        glBegin(GL_QUADS);
        float addX = 0;
        float addY = 0;
        for (int j = 0; j < 4; j++) {

            if (faces[i][j] == 1 || faces[i][j] == 2 || faces[i][j] == 6 || faces[i][j] == 5)
                addX = lengthX;
            else
                addX = -200;

            if (faces[i][j] == 0 || faces[i][j] == 1 || faces[i][j] == 4 || faces[i][j] == 5)
                addY = -200;

            else
                addY = 165;

            float addZ = ((faces[i][j] >= 4) ? 30 : 0);
            double POS[3] = { vertices[faces[i][j]][0] + x + addX  ,  vertices[faces[i][j]][1] + y + addY ,  vertices[faces[i][j]][2] + z + addZ };

            glTexCoord2d(((TexCoor[j].x) ? 10 : 0), ((TexCoor[j].y) ? 10 : 0));
            glVertex3dv(POS);
        }
        glEnd();
        glPopMatrix();

    }

}

void Wall::drawgCubic(float x, float y, float z, float lengthx, float lengthy, float lengthz,int roof,int wallout) {
    int tex;
    for (int i = 0; i < 6; i++) {
        if (i == 4)tex = roof;
        else tex = wallout;
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glBegin(GL_QUADS);
        for (int j = 0; j < 4; j++) {
            float addx = ((faces[i][j] == 1 || faces[i][j] == 2 || faces[i][j] == 5 || faces[i][j] == 6) ? lengthx : -lengthx);
            float addy = ((faces[i][j] == 3 || faces[i][j] == 2 || faces[i][j] == 7 || faces[i][j] == 6) ? lengthy : -lengthy);
            float addz = ((faces[i][j] == 1 || faces[i][j] == 2 || faces[i][j] == 0 || faces[i][j] == 3) ? lengthz : -lengthz);
            double POS[3] = { x + addx, y + addy, z + addz };
            if (j == 0) {
                glTexCoord2f(0.0f, 0.0f);
            }
            else if (j == 1) {
                glTexCoord2f(7.0f, 0.0f);
            }
            else if (j == 2) {
                glTexCoord2f(7.0f, 2.0f);
            }
            else {
                glTexCoord2f(0.0f, 2.0f);
            }
            glVertex3dv(POS);

            //  glTexCoord2f(TexCoor[j].x, TexCoor[j].y);
              //glVertex3dv(POS);
        }

        glEnd();
    }
}

void Wall::outerWall(float centerX, float centerY, float centerZ, float cubeSize, float wallLength, float wallWidth, int tex, int roof) {
    // Draw the four walls of the fence
    drawgCubic(centerX, centerY, centerZ + cubeSize / 2 + wallLength / 2, cubeSize, wallWidth, wallLength, 1 , tex);
    drawgCubic(centerX, centerY, centerZ - cubeSize / 2 - wallLength / 2, cubeSize, wallWidth, wallLength, 1 , tex);
    drawgCubic(centerX - cubeSize / 2 - wallLength / 2, centerY, centerZ, wallLength, wallWidth, cubeSize, 1 , tex);
    drawgCubic(centerX + cubeSize / 2 + wallLength / 2, centerY, centerZ, wallLength, wallWidth, cubeSize, 1 , tex);

    // Calculate the distance between cubes along the x-axis
    float distanceBetweenCubes = 1000.0f;

    // Calculate the initial x-coordinate for the first cube
    float initialX = centerX - cubeSize / 2 - wallLength / 2 + distanceBetweenCubes / 2 + 3 * (centerX);

    // Draw small cubes on top of each wall
    for (int i = 0; i < 20; i++) {
        float currentX = initialX + i * distanceBetweenCubes;

        // Draw a small cube on top of the front wall
        drawgCubic(currentX + 100, centerY + wallWidth + 0.01 * (wallWidth), centerZ + cubeSize / 2 + wallLength / 2,
            wallWidth / 6, cubeSize / 200, cubeSize / 150, 2 , tex);

        // Draw a small cube on top of the back wall
        drawgCubic(currentX, centerY + wallWidth + 0.01 * (wallWidth), centerZ - cubeSize / 2 - wallLength / 2,
            wallWidth / 6, cubeSize / 200, cubeSize / 210, 2 , tex);

        // Draw a small cube on top of the left wall
        drawgCubic(centerX - cubeSize / 2 - wallLength / 2 + wallLength * 0.7, centerY + wallWidth + 0.01 * wallWidth, currentX,
            wallWidth / 50, cubeSize / 200, cubeSize / 80, 2 , tex);

        // Draw a small cube on top of the right wall
        drawgCubic(centerX + cubeSize / 2 + wallLength / 2 - wallLength * 0.7, centerY + wallWidth + 0.01 * (wallWidth), currentX,
            wallWidth / 50, cubeSize / 200, cubeSize / 80, 2, tex);
    }
}