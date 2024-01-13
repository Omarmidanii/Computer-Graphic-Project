#include "Almawazin.h"

Almawazin::Almawazin(){}

Almawazin::Almawazin(float x, float y, float z, float r, float length,int soor) {
    //رسم البائكة 
    drawArc(x, y, z, r, 2, 0, soor);
    drawArc(x - (length * 0.083), y, z, r, 2, 0, soor);
    drawArc(x - (length * 0.1583), y, z, r, 2, 0, soor);
    drawArc(x - (length * 0.23), y, z, r, 2, 0, soor);

    // Translated(10,0,0);
    drawJamb(x + (length * 0.036), y, z, length * 0.00816, soor, 0);
    drawJamb(x - (length * 0.0416), y, z, length * 0.00816, soor, 0);
    drawJamb(x - (length * 0.12), y, z, length * 0.00816, soor, 0);
    drawJamb(x - (length * 0.196), y, z, length * 0.00816, soor, 0);
    drawJamb(x - (length * 0.27), y, z, length * 0.00816, soor, 0);
}


void Almawazin::drawArc(float x, float y, float z, float r, float p, float st, int tex)
{
    float numberofpoints = 100;
    glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_QUAD_STRIP);
    for (float i = st; i <= numberofpoints / p + st; i += 1) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numberofpoints);
        float dx = r * cosf(theta);
        float dy = r * sinf(theta);
        float ddx = (r + (r * 0.25)) * cosf(theta);
        float ddy = (r + (r * 0.25)) * sinf(theta);
        glTexCoord2f(i * p / numberofpoints, 0); glVertex3d(dx + x, dy + y, 0 + z);
        glTexCoord2f(i * p / numberofpoints, 1); glVertex3d(ddx + x, ddy + y, 0 + z);
    }
    glEnd();
}

void Almawazin::drawJamb(float x, float y, float z, float r, int tex, int number)
{
    float numberofpoints = 100;
    glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_QUAD_STRIP);
    for (float i = 0; i <= numberofpoints; i += 0.01) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numberofpoints);
        float dx = r * cosf(theta);
        float dy = r * sinf(theta);
        glTexCoord2f(i / numberofpoints, 0); glVertex3d(dx + x, y, z + dy);
        glTexCoord2f(i / numberofpoints, 1); glVertex3d(dx + x, y - (r * 20) - ((number == 1) ? 35 : 0), z + dy);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_QUAD_STRIP);
    for (float i = 0; i <= numberofpoints; i += 0.01) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numberofpoints);
        float dx = r * cosf(theta);
        float dy = r * sinf(theta);
        float dxx = (r + 0.1) * cosf(theta);
        float dyy = (r + 0.1) * sinf(theta);
        glTexCoord2f(i / numberofpoints, 1); glVertex3d(dx + x, y - (r * 20), z + dy);
        glTexCoord2f(i / numberofpoints, 1); glVertex3d(dxx + x, y - (r * 20.5) - ((number == 1) ? 35 : 0), z + dyy);
    }
    glEnd();
    // the middle cube in the bottom of the jamb 
    for (int i = 0; i < 6; i++) {
        glBindTexture(GL_TEXTURE_2D, tex);
        glBegin(GL_QUADS);
        for (int j = 0; j < 4; j++) {
            float addx = ((faces[i][j] == 1 || faces[i][j] == 2 || faces[i][j] == 5 || faces[i][j] == 6) ? r : -r);
            float addy = ((faces[i][j] == 7 || faces[i][j] == 2 || faces[i][j] == 3 || faces[i][j] == 6) ? r : -r);
            float addz = ((faces[i][j] == 0 || faces[i][j] == 1 || faces[i][j] == 2 || faces[i][j] == 3) ? (r * 6) : (r * 4.5));
            double POS[3] = { addx + x  ,addy + y - (r * 22) - ((number == 1) ? 35 : 0) , addz + z - (r * 5.2) };
            glTexCoord2d(TexCoor[j].x, TexCoor[j].y);
            glVertex3dv(POS);
        }
        glEnd();
    }

    // the upper cube in the bottom of the jamb 
    for (int i = 0; i < 6; i++) {
        glBindTexture(GL_TEXTURE_2D, tex);
        glBegin(GL_QUADS);
        for (int j = 0; j < 4; j++) {
            float addx = ((faces[i][j] == 0 || faces[i][j] == 3 || faces[i][j] == 4 || faces[i][j] == 7) ? -(r / 10) : (r / 10)) + ((faces[i][j] == 1 || faces[i][j] == 2 || faces[i][j] == 5 || faces[i][j] == 6) ? r : -r);
            float addy = ((faces[i][j] == 1 || faces[i][j] == 0 || faces[i][j] == 4 || faces[i][j] == 5) ? r : -(r / 2)) + ((faces[i][j] == 7 || faces[i][j] == 2 || faces[i][j] == 3 || faces[i][j] == 6) ? r : -r);
            float addz = ((faces[i][j] <= 3) ? -(r / 20) : r / 20) + ((faces[i][j] == 0 || faces[i][j] == 1 || faces[i][j] == 2 || faces[i][j] == 3) ? (r * 6) : (r * 4.5));
            double POS[3] = { x + addx , y - (r * 21) + addy - ((number == 1) ? 35 : 0) , z + addz - (r * 5.2) };
            glTexCoord2d(TexCoor[j].x, TexCoor[j].y);
            glVertex3dv(POS);
        }
        glEnd();
    }
    // the lower cube in the bottom of the jamb 
    for (int i = 0; i < 6; i++) {
        glBindTexture(GL_TEXTURE_2D, tex);
        glBegin(GL_QUADS);
        for (int j = 0; j < 4; j++) {
            float addx = ((faces[i][j] == 0 || faces[i][j] == 3 || faces[i][j] == 4 || faces[i][j] == 7) ? -(r / 10) : (r / 10)) + ((faces[i][j] == 1 || faces[i][j] == 2 || faces[i][j] == 5 || faces[i][j] == 6) ? r : -r);
            float addy = ((faces[i][j] == 1 || faces[i][j] == 0 || faces[i][j] == 4 || faces[i][j] == 5) ? r : -(r / 2)) + ((faces[i][j] == 7 || faces[i][j] == 2 || faces[i][j] == 3 || faces[i][j] == 6) ? r : -r);
            float addz = ((faces[i][j] <= 3) ? -(r / 20) : r / 20) + ((faces[i][j] == 0 || faces[i][j] == 1 || faces[i][j] == 2 || faces[i][j] == 3) ? (r * 6) : (r * 4.5));
            double POS[3] = { x + addx , y - (r * 23.5) + addy - ((number == 1) ? 35 : 0) , z + addz - (r * 5.2) };
            glTexCoord2d(TexCoor[j].x, TexCoor[j].y);
            glVertex3dv(POS);
        }
        glEnd();
    }


}