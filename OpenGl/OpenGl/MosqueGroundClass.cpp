#include "MosqueGround.h"


MosqueGround::MosqueGround(float x, float y, float z, float length, int demoAlshek) {
    for (int i = 0; i < 6; i++) {
        if (i == 5)

            continue;

        glBindTexture(GL_TEXTURE_2D, demoAlshek);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glBegin(GL_QUADS);
        for (int j = 0; j < 4; j++) {
            float addx = 0;
            float addy = 0;
            float addz = 0;
            if (faces[i][j] <= 3)
            {   //right
                addz = length;
            }
            if (faces[i][j] > 3) {
                //left
                addz = -length;
            }
            if (faces[i][j] == 2 || faces[i][j] == 5 || faces[i][j] == 6 || faces[i][j] == 1) {
                //front
                addx = length;

            }
            else {
                //bacck
                addx = -length;
            }

            if (faces[i][j] == 0 || faces[i][j] == 1 || faces[i][j] == 4 || faces[i][j] == 5) {
                addy = -70;
            }
            else {
                addy = 0;
            }

            double POS[3] = { vertices[faces[i][j]][0] + x + addx ,vertices[faces[i][j]][1] + y + addy , vertices[faces[i][j]][2] + z + addz };
            glTexCoord2d(((TexCoor[j].x) ? 10 : 0), ((TexCoor[j].y) ? 10 : 0));
            glVertex3dv(POS);
        }
        glEnd();
    }
}