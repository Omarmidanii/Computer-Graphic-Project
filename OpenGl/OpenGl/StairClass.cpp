#include "Stair.h"

Stair::Stair(){}

Stair::Stair(float x, float y, float z, float lengthx, float lengthy, float lengthz, int number,int stone1) {
    glPushMatrix();
    glTranslatef(0, 0.5, 0);
    for (int i = 0; i < number; i++) {
        glTranslated(0, 5, 0);
        glBindTexture(GL_TEXTURE_2D, stone1);

        for (int i = 0; i < 6; i++) {
            glPushMatrix();

            glBegin(GL_QUADS);
            for (int j = 0; j < 6; j++) {
                float addX = 0;
                if (faces[i][j] == 1 || faces[i][j] == 2 || faces[i][j] == 6 || faces[i][j] == 5)
                    addX = lengthx;
                else
                    addX = -(lengthx + 85);
                float addz = ((faces[i][j] >= 4) ? 8 : 0);
                float addy = 0;
                if (faces[i][j] == 2 || faces[i][j] == 3 || faces[i][j] == 6 || faces[i][j] == 7)addy = 5;
                double POS[3] = { vertices[faces[i][j]][0] + x + addX ,  vertices[faces[i][j]][1] + y + lengthy + addy ,  vertices[faces[i][j]][2] + z + lengthz + addz };

                glTexCoord2d(((TexCoor[j].x) ? 5 : 0), TexCoor[j].y);
                glVertex3dv(POS);
            }
            glEnd();
            glPopMatrix();
        }
        lengthz += 8;
        lengthx += 0.6;
    }
    glPopMatrix();

    glPushMatrix();
    glTranslated(130, 85, 130);
    StairEdge(x, y, z,stone1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-210, 85, 130);
    StairEdge(x, y, z,stone1);
    glPopMatrix();


}

void Stair::StairEdge(float x, float y, float z,int stone1) {
    for (int i = 0; i < 6; i++) {
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, stone1);

        glBegin(GL_QUADS);
        float addX = 0;
        float addY = 0;
        for (int j = 0; j < 4; j++) {

            if (faces[i][j] == 1 || faces[i][j] == 2 || faces[i][j] == 6 || faces[i][j] == 5)
                addX = 15;
            else
                addX = -22;


            if (faces[i][j] == 2 || faces[i][j] == 3) {
                addY = 40;
            }
            else if (faces[i][j] == 6 || faces[i][j] == 7) {
                addY = 170;
            }


            float addZ = ((faces[i][j] >= 4) ? 100 : -20);
            double POS[3] = { vertices[faces[i][j]][0] + x + addX  ,  vertices[faces[i][j]][1] + y + addY ,  vertices[faces[i][j]][2] + z + addZ };

            glTexCoord2d(TexCoor[j].x, ((TexCoor[j].y) ? 5 : 0));
            glVertex3dv(POS);
        }
        glEnd();
        glPopMatrix();

    }

}