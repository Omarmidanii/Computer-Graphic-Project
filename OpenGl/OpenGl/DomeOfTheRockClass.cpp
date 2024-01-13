#include "DomeOfRock.h"



DomeOfTheRock::DomeOfTheRock()
{
}


void DomeOfTheRock::setTexture(const map<string, int>& tex) {
    this->domeOfRockTex = tex;
}

void DomeOfTheRock::drawArc(float x, float y, float z, float r, float p, float st, int tex)
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

void DomeOfTheRock::drawBArc(float x, float y, float z, float r, float p, float st, int tex) {
    float numberofpoints = 100;
    glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_QUAD_STRIP);
    for (float i = st; i <= numberofpoints / p + st; i += 0.01) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numberofpoints);
        float ddx = (r + (r * 0.25)) * cosf(theta);
        float ddy = (r + (r * 0.25)) * sinf(theta);
        glTexCoord2f(i * p / numberofpoints, 0); glVertex3d(ddx + x, ddy + y, 0 + z);
        glTexCoord2f(i * p / numberofpoints, 1); glVertex3d(ddx + x, ddy + y, 0 + z - r + 0.02);
    }
    glEnd();
    glBegin(GL_QUAD_STRIP);
    for (float i = st; i <= numberofpoints / p + st; i += 0.01) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numberofpoints);
        float ddx = (r * cosf(theta));
        float ddy = (r * sinf(theta));
        glTexCoord2f(i * p / numberofpoints, 0); glVertex3d(ddx + x, ddy + y, 0 + z);
        glTexCoord2f(i * p / numberofpoints, 1); glVertex3d(ddx + x, ddy + y, 0 + z - r + 0.02);
    }
    glEnd();
}

void DomeOfTheRock::drawJamb(float x, float y, float z, float r, int tex, int number)
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

void DomeOfTheRock::buildArcDome(float x, float y, float z, float r) {
    // Front Arc
    drawArc(x, y, z, r, 2, 0, this->domeOfRockTex["arc"]);
    // between them
    drawBArc(x, y, z, r, 2, 0, this->domeOfRockTex["decor1"]);
    // Back Arc
    drawArc(x, y, z - r + 0.02, r, 2, 0, this->domeOfRockTex["arc"]);
    // left back jamb  
    drawJamb(x - (r + (r * 0.12)), y - (r * 0.50), z - r + (r * 0.125), r * 0.1, this->domeOfRockTex["marble1"], 1);
    // right front jamb
    drawJamb(x + (r + (r * 0.12)), y - (r * 0.50), z - (r * 0.20), r * 0.1, this->domeOfRockTex["marble1"], 1);
    // right2 front jamb
    drawJamb(x + (r + (r * 1.12)), y - (r * 0.50), z - (r * 0.20), r * 0.1, this->domeOfRockTex["marble1"], 1);
    // right3 front jamb
    drawJamb(x + (r + (r * 2.12)), y - (r * 0.50), z - (r * 0.20), r * 0.1, this->domeOfRockTex["marble1"], 1);
    // right4 front jamb
    drawJamb(x + (r + (r * 3.12)), y - (r * 0.50), z - (r * 0.20), r * 0.1, this->domeOfRockTex["marble1"], 1);
    // right back jamb
    drawJamb(x + (r + (r * 0.12)), y - (r * 0.50), z - r + (r * 0.125), r * 0.1, this->domeOfRockTex["marble1"], 1);
    // left front jamb
    drawJamb(x - (r + (r * 0.12)), y - (r * 0.50), z - (r * 0.20), r * 0.1, this->domeOfRockTex["marble1"], 1);
    // left2 front jamb
    drawJamb(x - (r + (r * 1.12)), y - (r * 0.50), z - (r * 0.20), r * 0.1, this->domeOfRockTex["marble1"], 1);
    // left3 front jamb
    drawJamb(x - (r + (r * 2.12)), y - (r * 0.50), z - (r * 0.20), r * 0.1, this->domeOfRockTex["marble1"], 1);
    // left4 front jamb
    drawJamb(x - (r + (r * 3.12)), y - (r * 0.50), z - (r * 0.20), r * 0.1, this->domeOfRockTex["marble1"], 1);

    int tex;
    // the up left side of the arc 
    for (int i = 0; i < 6; i++) {
        if (i == 0)tex = this->domeOfRockTex["arc1"];
        else tex = this->domeOfRockTex["decor1"];
        glBindTexture(GL_TEXTURE_2D, tex);
        glBegin(GL_QUADS);
        for (int j = 0; j < 4; j++) {
            float addx = ((faces[i][j] == 2 || faces[i][j] == 1 || faces[i][j] == 6 || faces[i][j] == 5) ? -r : -(r + (r * 0.25)));
            float addy = (((faces[i][j] == 2 || faces[i][j] == 6) && (i <= 2)) ? (r * 0.75) : ((faces[i][j] == 3 || faces[i][j] == 7) ? (r * 0.65) : 0));
            float addz = ((faces[i][j] >= 4) ? -r : 0);
            double POS[3] = { x + addx , y + addy,z + addz + 0.01 };
            glTexCoord2d(1 - TexCoor[j].x, TexCoor[j].y);
            glVertex3dv(POS);
        }
        glEnd();
    }
    //the up right side of the arc 
    for (int i = 0; i < 6; i++) {
        if (i == 0)tex = this->domeOfRockTex["arc1"];
        else tex = this->domeOfRockTex["decor1"];
        glBindTexture(GL_TEXTURE_2D, tex);
        glBegin(GL_QUADS);
        for (int j = 0; j < 4; j++) {
            float addx = ((faces[i][j] == 2 || faces[i][j] == 1 || faces[i][j] == 6 || faces[i][j] == 5) ? r : (r + (r * 0.25)));
            float addy = (((faces[i][j] == 2 || faces[i][j] == 6) && (i <= 2)) ? (r * 0.75) : ((faces[i][j] == 3 || faces[i][j] == 7) ? (r * 0.65) : 0));
            float addz = ((faces[i][j] >= 4) ? -r : 0);
            double POS[3] = { x + addx , y + addy,z + addz + 0.01 };
            glTexCoord2d(1 - TexCoor[j].x, TexCoor[j].y);
            glVertex3dv(POS);
        }
        glEnd();
    }
    //the bottom right side of the arc 
    for (int i = 0; i < 6; i++) {
        glBindTexture(GL_TEXTURE_2D, this->domeOfRockTex["marble2"]);
        glBegin(GL_QUADS);
        for (int j = 0; j < 4; j++) {
            float addx = ((faces[i][j] == 2 || faces[i][j] == 1 || faces[i][j] == 6 || faces[i][j] == 5) ? r : (r + (r * 0.25)));
            float addy = (((faces[i][j] == 2 || faces[i][j] == 6 || faces[i][j] == 3 || faces[i][j] == 7) ? (r * 0.5) : 0));
            float addz = ((faces[i][j] >= 4) ? -r : 0);
            if (faces[i][j] == 0 || faces[i][j] == 1)addz = -(r * 0.125);
            double POS[3] = { x + addx , y + addy - (r * 0.50),z + addz + 0.01 };
            glTexCoord2d(TexCoor[j].x, TexCoor[j].y);
            glVertex3dv(POS);
        }
        glEnd();
    }
    //the bottom left side of the arc 
    for (int i = 0; i < 6; i++) {
        glBindTexture(GL_TEXTURE_2D, this->domeOfRockTex["marble2"]);
        glBegin(GL_QUADS);
        for (int j = 0; j < 4; j++) {
            float addx = ((faces[i][j] == 2 || faces[i][j] == 1 || faces[i][j] == 6 || faces[i][j] == 5) ? -r : -(r + (r * 0.25)));
            float addy = (((faces[i][j] == 2 || faces[i][j] == 6 || faces[i][j] == 3 || faces[i][j] == 7) ? (r * 0.5) : 0));
            float addz = ((faces[i][j] >= 4) ? -r : 0);
            if (faces[i][j] == 0 || faces[i][j] == 1)addz = -(r * 0.125);
            double POS[3] = { x + addx , y + addy - (r * 0.50),z + addz + 0.01 };
            glTexCoord2d(TexCoor[j].x, TexCoor[j].y);
            glVertex3dv(POS);
        }
        glEnd();
    }
    //right rectangular prism 
    for (int i = 0; i < 6; i++) {
        glBindTexture(GL_TEXTURE_2D, this->domeOfRockTex["wood"]);
        glBegin(GL_QUADS);
        for (int j = 0; j < 4; j++) {
            float addx = ((faces[i][j] == 2 || faces[i][j] == 1 || faces[i][j] == 6 || faces[i][j] == 5) ? (r + (r * 0.25)) : (r + (r * 3.3)));
            float addy = (((faces[i][j] == 2 || faces[i][j] == 6 || faces[i][j] == 3 || faces[i][j] == 7) ? (r * 0.2) : 0));
            float addz = ((faces[i][j] >= 4) ? -r : 0);
            double POS[3] = { x + addx , y + addy - (r * 0.50),z + addz + 0.01 };
            glTexCoord2d(TexCoor[j].x, TexCoor[j].y);
            glVertex3dv(POS);
        }
        glEnd();
    }
    //left rectangular prism 
    for (int i = 0; i < 6; i++) {
        glBindTexture(GL_TEXTURE_2D, this->domeOfRockTex["wood"]);
        glBegin(GL_QUADS);
        for (int j = 0; j < 4; j++) {
            float addx = ((faces[i][j] == 2 || faces[i][j] == 1 || faces[i][j] == 6 || faces[i][j] == 5) ? -(r + (r * 0.25)) : -(r + (r * 3.3)));
            float addy = (((faces[i][j] == 2 || faces[i][j] == 6 || faces[i][j] == 3 || faces[i][j] == 7) ? (r * 0.2) : 0));
            float addz = ((faces[i][j] >= 4) ? -r : 0);
            double POS[3] = { x + addx , y + addy - (r * 0.50),z + addz + 0.01 };
            glTexCoord2d(TexCoor[j].x, TexCoor[j].y);
            glVertex3dv(POS);
        }
        glEnd();
    }
    // the floor
        for (int i = 0; i < 6; i++) {
            glBindTexture(GL_TEXTURE_2D, this->domeOfRockTex["decor7"]);
            glBegin(GL_QUADS);
            for (int j = 0; j < 4; j++) {
                float addx = ((faces[i][j] == 2 || faces[i][j] == 1 || faces[i][j] == 6 || faces[i][j] == 5) ? (r + (r * 3.3)) : -(r + (r * 3.3)));
                float addy = (((faces[i][j] == 2 || faces[i][j] == 6 || faces[i][j] == 3 || faces[i][j] == 7) ? (r * 0.4) : 0));
                float addz = ((faces[i][j] >= 4) ? -r : 0);
                double POS[3] = { x + addx , y + addy - 100,z + addz + 0.01 };
                glTexCoord2d(TexCoor[j].x, TexCoor[j].y);
                glVertex3dv(POS);
            }
            glEnd();
        }



}


void DomeOfTheRock::drawoctagon(float length, int tex) {
    glBindTexture(GL_TEXTURE_2D, tex);
    int second;
    glBegin(GL_QUADS);
    for (int i = 0; i < (int)v.size(); i++) {
        if (i + 1 < v.size())second = i + 1;
        else second = 0;
        glTexCoord2d(0, 1); glVertex3f(v[i].x, v[i].y, v[i].z);
        glTexCoord2d(1, 1); glVertex3f(v[second].x, v[second].y, v[second].z);
        glTexCoord2d(1, 0); glVertex3f(v[second].x, v[second].y - length, v[second].z);
        glTexCoord2d(0, 0); glVertex3f(v[i].x, v[i].y - length, v[i].z);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, this->domeOfRockTex["leftfrontwall"]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1); glVertex3f(v[0].x, v[0].y, v[0].z + 0.5f);
    glTexCoord2d(1, 1); glVertex3f(v[0].x + length / 3 + (0.08 * length), v[0].y, v[0].z + 0.5f);
    glTexCoord2d(1, 0); glVertex3f(v[0].x + length / 3 + (0.08 * length), v[0].y - length, v[0].z + 0.5f);
    glTexCoord2d(0, 0); glVertex3f(v[0].x, v[0].y - length, v[0].z + 0.5f);
    glEnd();
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1); glVertex3f(v[1].x, v[1].y, v[1].z + 0.5f);
    glTexCoord2d(1, 1); glVertex3f(v[1].x - length / 3 - (0.08 * length), v[1].y, v[1].z + 0.5f);
    glTexCoord2d(1, 0); glVertex3f(v[1].x - length / 3 - (0.08 * length), v[1].y - length, v[1].z + 0.5f);
    glTexCoord2d(0, 0); glVertex3f(v[1].x, v[1].y - length, v[1].z + 0.5f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, this->domeOfRockTex["door"]);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0); glVertex3f(v[0].x + length / 3 + (0.22 * length), v[0].y - length, v[0].z + 0.5f);
    glTexCoord2d(1, 0); glVertex3f(v[1].x - length / 3 - (0.22 * length), v[1].y - length, v[1].z + 0.5f);
    glTexCoord2d(1, 1); glVertex3f(v[1].x - length / 3 - (0.22 * length), v[1].y - length + length / 3 + 10, v[1].z + 0.5f);
    glTexCoord2d(0, 1); glVertex3f(v[0].x + length / 3 + (0.22 * length), v[0].y - length + length / 3 + 10, v[0].z + 0.5f);
    glEnd();
   

    // back door
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0); glVertex3f(v[5].x + length / 3 + (0.22 * length), v[5].y - length, v[5].z - 0.5f);
    glTexCoord2d(1, 0); glVertex3f(v[4].x - length / 3 - (0.22 * length), v[4].y - length, v[4].z - 0.5f);
    glTexCoord2d(1, 1); glVertex3f(v[4].x - length / 3 - (0.22 * length), v[4].y - length + length / 3 + 10, v[4].z - 0.5f);
    glTexCoord2d(0, 1); glVertex3f(v[5].x + length / 3 + (0.22 * length), v[5].y - length + length / 3 + 10, v[5].z - 0.5f);
    glEnd();
    // right door
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0); glVertex3f(v[2].x + 0.5f, v[2].y - length, v[2].z - length / 3 - (0.22 * length));
    glTexCoord2d(1, 0); glVertex3f(v[3].x + 0.5f, v[3].y - length, v[3].z + length / 3 + (0.30 * length));
    glTexCoord2d(1, 1); glVertex3f(v[3].x + 0.5f, v[3].y - length + length / 3 + 10, v[3].z + length / 3 + (0.30 * length));
    glTexCoord2d(0, 1); glVertex3f(v[2].x + 0.5f, v[2].y - length + length / 3 + 10, v[2].z - length / 3 - (0.22 * length));
    glEnd();
    // left door
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0); glVertex3f(v[7].x - 0.5f, v[7].y - length, v[7].z - length / 3 - (0.22 * length));
    glTexCoord2d(1, 0); glVertex3f(v[6].x - 0.5f, v[6].y - length, v[6].z + length / 3 + (0.30 * length));
    glTexCoord2d(1, 1); glVertex3f(v[6].x - 0.5f, v[6].y - length + length / 3 + 10, v[6].z + length / 3 + (0.30 * length));
    glTexCoord2d(0, 1); glVertex3f(v[7].x - 0.5f, v[7].y - length + length / 3 + 10, v[7].z - length / 3 - (0.22 * length));
    glEnd();

}

void DomeOfTheRock::drawceil(float x, float y, float z, int tex) {
    glBindTexture(GL_TEXTURE_2D, tex);
    int second;
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i < (int)v.size(); i++) {
        if (i + 1 < v.size())second = i + 1;
        else second = 0;
        glTexCoord2d(0, 0); glVertex3f(v[i].x, v[i].y, v[i].z);
        glTexCoord2d(0, 1); glVertex3f(v[second].x, v[second].y, v[second].z);
        glTexCoord2d(0.5, 1); glVertex3f(x, y, z);

    }
    glEnd();
   
  
}

void DomeOfTheRock::drawpolygon(float x, float y, float z, float radius, float length, int numVertices, int tex) {
    const int numVertices1 = 1100;
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

void DomeOfTheRock::drawdome(float a, float b, float c, float radius, int tex, int tex1, int sizeofbase) {

    glPushMatrix();
    glTranslatef(0, 0, -50);
    //======= Drawing The Crescent =======//
    // Draw the crescent shape using GL_TRIANGLE_FAN
    float numberofpoints = 50;
    glBindTexture(GL_TEXTURE_2D, this->domeOfRockTex["marble"]);
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
        drawpolygon(a, b - 30, c, radius, 67, 50, tex);
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
    glPopMatrix();
}
// 10 -110 20 20
void DomeOfTheRock::drawBodyDomeoftheRock(float x, float y, float z, float r) {
    float length = r * 12.5;
    float d = 40;
    // x =  -160 , y = 100 , z = -0.01
    v.push_back({ x - r * 6.5f - d,y - r * 3 + length ,z - r - 0.01f });
    v.push_back({ x - r * 6.5f + length + d, y - r * 3 + length , z - r - 0.01f });
    v.push_back({ x - r * 6.5f + length + (length * 0.90f) + d, y - r * 3 + length , z - r - length });
    v.push_back({ x - r * 6.5f + length + (length * 0.90f) + d, y - r * 3 + length, z - r - 2 * length });
    v.push_back({ x - r * 6.5f + length + d , y - r * 3 + length, z - r - 3 * length });
    v.push_back({ x - r * 6.5f - d, y - r * 3 + length, z - r - 3 * length });
    v.push_back({ x - r * 6.5f - (length * 0.90f) - d, y - r * 3 + length, z - r - 2 * length });
    v.push_back({ x - r * 6.5f - (length * 0.90f) - d, y - r * 3 + length, z - r - length });
    // drawing the Arc of The Door
   //front
    buildArcDome(x - (r * 0.25), y + 35, z, r);


    // right
        /*glPushMatrix();
        glTranslated(x - r * 6.5f + length + (length * 0.90f) + d,0, z - r - length);
        glRotated(-90, 0, 1, 0);
        buildArcDome(x - (r * 0.25), y + 35, z, r);
        glPopMatrix();*/
    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glTranslated(-7, 0, 3);
    buildArcDome(-z + r * (0.975 * r), y + 35, x + r * (1.01f * r), r);
    glPopMatrix();
    // left
    glPushMatrix();
    glTranslated(x - (r * 0.25), 0, z);
    glRotated(-90, 0, 1, 0);
    glTranslated(-5, 0, 12);
    buildArcDome(z - r * 20.0, y + 35, x + r * 19.5f, r);
    glPopMatrix();
    // back
    glPushMatrix();
    glTranslated(x - (r * 0.25), 0, z);
    glRotated(180, 0, 1, 0);
    glTranslated(-10, 0, 0);
    buildArcDome(x - (r * 0.25), y + 35, z + r * 38.5, r);
    glPopMatrix();
    // drawing the main bpdy
    drawoctagon(r * 12.5f, this->domeOfRockTex["frontwall"]);
    float centerx = (8 * (x - r * 6.5f) + 5 * (r * 12.5) + 2 * ((r * 12.5) * 0.90)) / 8;
    float centery = y - r * 3 + r * 12.5;
    float centerz = (8 * (z - r) - 10 * (r * 12.5)) / 8;
    drawceil(centerx, centery, centerz, this->domeOfRockTex["marble2"]);
    drawdome(centerx - (r * 5), centery + (r * 3), centerz, (r * 12.5), this->domeOfRockTex["dome5"], this->domeOfRockTex["dome"], (r * 300));
    // floor
    glBindTexture(GL_TEXTURE_2D, domeOfRockTex["decor7"]);
    int second;
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i < (int)v.size(); i++) {
        if (i + 1 < v.size())second = i + 1;
        else second = 0;
        glTexCoord2d(0, 0); glVertex3f(v[i].x, v[i].y - length, v[i].z);
        glTexCoord2d(0, 1); glVertex3f(v[second].x, v[second].y - length, v[second].z);
        glTexCoord2d(0.5, 1); glVertex3f(centerx, centery - length, centerz);

    }
    glEnd();

}