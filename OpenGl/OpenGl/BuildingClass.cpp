#include "Building.h"

Building::Building()
{
}


void Building::setTexture(const map<string, int>& tex) {
    this->buildingTex = tex;
}

void Building::drawpolygon(float x, float y, float z, float radius, float length, int numVertices, int tex) {
    const int numVertices1 = 20;
    // Angle between each vertex
    float angleIncrement = 2.0f * M_PI / numVertices;

    // Array to hold the vertices
    GLfloat verticess1[numVertices1][3];

    // Calculate the position of each vertex
    for (int i = 0; i < numVertices; ++i)
    {
        float angle = i * angleIncrement;
        verticess1[i][0] = radius * cos(angle) + x;
        verticess1[i][1] = y + 30;
        verticess1[i][2] = radius * sin(angle) + z;
    }
    glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_QUADS);
    for (int i = 0; i < numVertices; ++i)
    {
        int second = 0;
        if (i + 1 < numVertices)second = i + 1;
        else second = 0;
        glTexCoord2f(0, 0); glVertex3f(verticess1[i][0], verticess1[i][1] - length, verticess1[i][2]);
        glTexCoord2f(1, 0); glVertex3f(verticess1[second][0], verticess1[second][1] - length, verticess1[second][2]);
        glTexCoord2f(1, 1); glVertex3fv(verticess1[second]);
        glTexCoord2f(0, 1); glVertex3fv(verticess1[i]);
    }
    glEnd();
}

void Building::drawdome(float a, float b, float c, float radius, int tex, int tex1, int sizeofbase) {
    glLineWidth(10.0f);
    //======= Drawing The Crescent =======//
    // Draw the crescent shape using GL_TRIANGLE_FAN
    float numberofpoints = 50;
    glBindTexture(GL_TEXTURE_2D, this->buildingTex["marble"]);
    glBegin(GL_QUAD_STRIP);
    for (float i = 0; i <= numberofpoints; i += 1) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numberofpoints);
        float dx = (0.1 * radius) * cosf(theta);
        float dy = (0.1 * radius) * sinf(theta);
        float ddx = ((0.1 * radius) + ((0.1 * radius) * 0.25)) * cosf(theta);
        float ddy = ((0.1 * radius) + ((0.1 * radius) * 0.25)) * sinf(theta);
        glTexCoord2f(i / numberofpoints, 0); glVertex3d(dx + a, dy + b + (2 * radius) + (0.1f * radius), 0 + c);
        glTexCoord2f(i / numberofpoints, 1); glVertex3d(ddx + a, ddy + b + (2 * radius) + (0.1f * radius), 0 + c);
    }
    glEnd();
    glBegin(GL_LINES);
    glTexCoord2f(0, 0); glVertex3f(a, radius + b, c);
    glTexCoord2f(1, 1); glVertex3f(a, radius * 2 + b, c);
    glEnd();


    //======= Drawing The Base Of The Dome =======//
    if (sizeofbase)
        drawpolygon(a, b - 30, c, radius + (radius * 0.2), 67, 6, tex);
    //======= Drawing The Main Dome =======//
    glPushMatrix();
    glTranslated(0, b, 0);
    glRotated(90, 1, 0, 0);
    glBindTexture(GL_TEXTURE_2D, tex1);
    for (int i = 0; i < slices / 2; i++) {
        float lat0 = (float)M_PI * (-0.5f + (float)i / slices);
        float z0 = sin(lat0);
        float zr0 = cos(lat0);

        float lat1 = (float)M_PI * (-0.5f + (float)(i + 1) / slices);
        float z1 = sin(lat1);
        float zr1 = cos(lat1);
        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= stacks; j++) {
            float lng = (float)2 * M_PI * (float)j / stacks;
            float x = cos(lng);
            float y = sin(lng);
            glTexCoord2f((float)j * 2 / stacks, (float)i * 2 / slices);
            glVertex3f(x * zr0 * radius + a, y * zr0 * radius + c, z0 * radius);
            glTexCoord2f((float)j * 2 / stacks, (float)(i + 1) * 2 / slices);
            glVertex3f(x * zr1 * radius + a, y * zr1 * radius + c, z1 * radius);
        }
        glEnd();
    }
    glPopMatrix();
}

void Building::drawFirstHouse(float x, float y, float z) {
    drawdome(x + 50, y + 155, z + 25, 30, this->buildingTex["demoAlshek"], this->buildingTex["demoAlshek"], 0);
    drawdome(x - 60, y + 155, z + 25, 30, this->buildingTex["demoAlshek"], this->buildingTex["demoAlshek"], 0);
    // drawArc(x - 30, y, z - 300, 2, 2, 0, hello2);
    for (int i = 0; i < 6; i++) {


        if (i == 2) {
            // drawasmaa(12, -50, 1000, 50);
            glBindTexture(GL_TEXTURE_2D, this->buildingTex["demoAlshekWall"]);
        }



        else {
            glBindTexture(GL_TEXTURE_2D, this->buildingTex["demoAlshek"]);
        }


        glBegin(GL_QUADS);
        for (int j = 0; j < 4; j++) {
            float addx = 0;
            float addy = 0;
            float addz = 0;
            if (faces[i][j] <= 3)
            {   //right
                addz = 50;
            }
            if (faces[i][j] > 3) {
                //left
                addz = -30;
            }
            if (faces[i][j] == 2 || faces[i][j] == 5 || faces[i][j] == 6 || faces[i][j] == 1) {
                //front
                addx = 100;

            }
            if (faces[i][j] == 0 || faces[i][j] == 4 || faces[i][j] == 7 || faces[i][j] == 3) {
                //bacck
                addx = -100;

            }
            if (faces[i][j] == 0 || faces[i][j] == 4 || faces[i][j] == 1 || faces[i][j] == 5) {
                addy = +160;
            }


            double POS[3] = {vertices[faces[i][j]][0] + x + addx ,vertices[faces[i][j]][1] + y + addy, vertices[faces[i][j]][2] + z + addz };
            glTexCoord2d(TexCoor[j].x, 1 - TexCoor[j].y);
            glVertex3dv(POS);
        }
        glEnd();
    }

}

void Building::drawSecondHouse(float x, float y, float z) {
    drawdome(x + 10, y + 55, z + 17, 30, this->buildingTex["demoAlshek"], this->buildingTex["demoAlshek"], 0);
    for (int i = 0; i < 6; i++) {
        if (i == 2) {

            glBindTexture(GL_TEXTURE_2D, this->buildingTex["door2"]);
        }


        else {
            glBindTexture(GL_TEXTURE_2D, this->buildingTex["demoAlshek"]);
        }


        glBegin(GL_QUADS);
        for (int j = 0; j < 4; j++) {
            float addx = 0;
            float addy = 0;
            float addz = 0;
            if (faces[i][j] <= 3)
            {   //right
                addz = 30;
            }
            if (faces[i][j] > 3) {
                //left
                addz = -30;
            }
            if (faces[i][j] == 2 || faces[i][j] == 5 || faces[i][j] == 6 || faces[i][j] == 1) {
                //front
                addx = 70;

            }
            if (faces[i][j] == 0 || faces[i][j] == 4 || faces[i][j] == 7 || faces[i][j] == 3) {
                //bacck
                addx = -70;

            }

            if (faces[i][j] == 0 || faces[i][j] == 4 || faces[i][j] == 1 || faces[i][j] == 5) {
                addy = -80;
            }
            if (faces[i][j] == 2 || faces[i][j] == 3 || faces[i][j] == 7 || faces[i][j] == 6) {
                addy = +60;
            }


            double POS[3] = { vertices[faces[i][j]][0] + x + addx ,vertices[faces[i][j]][1] + y + addy, vertices[faces[i][j]][2] + z + addz };
            glTexCoord2d(TexCoor[j].x, TexCoor[j].y);
            glVertex3dv(POS);
        }
        glEnd();
    }

}