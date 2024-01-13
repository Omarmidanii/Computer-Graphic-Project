#include"Qmosque.h"
#include "texture.h"

Qmosque::Qmosque()
{
	qmosque();
    // Qmosque
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    DOORS = LoadTexture("saker/door.bmp" , 255);
    carpet = LoadTexture("saker/carpet.bmp" , 255);
    ROOF2UP = LoadTexture("saker/roof2.bmp", 255);
    ROOF2DOWN = LoadTexture("saker/mainroof.bmp" , 255);
    roof = LoadTexture("saker/roof.bmp" , 255);
    sideroof = LoadTexture("saker/sideroof.bmp" , 255);
    cylinder1 = LoadTexture("saker/cylinder1.bmp", 255);
    cylinder2 = LoadTexture("saker/cylinder2.bmp", 255);
    cylinder3 = LoadTexture("saker/cylinder3.bmp", 255);
    cuboid1 = LoadTexture("saker/cuboid1.bmp", 255);
    cuboid2 = LoadTexture("saker/cuboid2.bmp", 255);
    cuboid3 = LoadTexture("saker/cuboid3.bmp", 255);
    MAINBLOCK = LoadTexture("saker/out3.bmp", 255);
    fence = LoadTexture("saker/fence2.bmp", 255);
    pedestal = LoadTexture("saker/pedestal2.bmp", 255);
    pedestal2 = LoadTexture("saker/pedestal.bmp", 255);
    extension = LoadTexture("saker/extension2.bmp", 255);
    mainroof = LoadTexture("saker/mainroof.bmp", 255);
    subroof = LoadTexture("saker/subroof.bmp", 255);
    specialroof = LoadTexture("saker/specialroof.bmp", 255);
    inside = LoadTexture("saker/inside.bmp", 255);
    window1 = LoadTexture("saker/inner-window.bmp", 255);
    window2 = LoadTexture("saker/smallwindow.bmp", 255);
    window3 = LoadTexture("saker/window3.bmp", 255);
    sidedoor_i = LoadTexture("saker/sidedoor.bmp", 255);
    sidedoor_o = LoadTexture("saker/sidedoor-out.bmp", 255);
    emam = LoadTexture("saker/emam.bmp", 255);
    glass = LoadTexture("glass.bmp" , 100);
   
}

void Qmosque::drawTexturedCuboid(GLuint texture, float width, float height, float depth, float xpos, float ypos, float zpos, float s, float t) {
    GLfloat vertices[8][3] = {
{-0.5, -0.5, 0.5}, { 0.5, -0.5, 0.5 }, { 0.5, 0.5, 0.5 }, { -0.5, 0.5, 0.5 },  // vertices for the front face
{ -0.5, -0.5, -0.5 }, { 0.5, -0.5, -0.5 }, { 0.5, 0.5, -0.5 }, { -0.5, 0.5, -0.5 }  // vertices for the back face
    };

    // Indices for the 6 faces of the cuboid
    GLint faces[6][4] = {
        {0, 1, 2, 3},  // front face
        {1, 5, 6, 2},  // right face
        {5, 4, 7, 6},  // back face
        {4, 0, 3, 7},  // left face
        {3, 2, 6, 7},  // top face
        {4, 5, 1, 0}   // bottom face
    };
    GLfloat normals[6][3] = {
        {0.0, 0.0, 1.0},  // front face
        {1.0, 0.0, 0.0},  // right face
        {0.0, 0.0, -1.0},  // back face
        {-1.0, 0.0, 0.0},  // left face
        {0.0, 1.0, 0.0},  // top face
        {0.0, -1.0, 0.0}   // bottom face
    };
    // Enable Texture Mapping and set properties
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glPushMatrix();
    // Translate the cuboid to the desired position
    glTranslatef(xpos, ypos, zpos);

    // Scale the cuboid to the desired size
    glScalef(width, height, depth);

    // Draw the six faces of the cuboid
    glBegin(GL_QUADS);
    for (int i = 0; i < 6; ++i) {
        glNormal3fv(&normals[i][0]);
        
        glTexCoord2f(0.0f, 0.0f); glVertex3fv(&vertices[faces[i][0]][0]);
        glTexCoord2f(s, 0.0f); glVertex3fv(&vertices[faces[i][1]][0]);
        glTexCoord2f(s, t); glVertex3fv(&vertices[faces[i][2]][0]);
        glTexCoord2f(0.0f, t); glVertex3fv(&vertices[faces[i][3]][0]);
    }
    glEnd();
    glPopMatrix();
    // Disable Texture Mapping
    glDisable(GL_TEXTURE_2D);
}
// y = 7.4 , x = 22 , z = 16

void Qmosque::drawcylinder(GLuint texture, int numSegments, float radius, float height) {

    // Enable Texture Mapping and set properties
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glRotatef(90, 1.0f, 0.0f, 0.0f);
    // Draw the side of the cylinder
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= numSegments; i++) {
        float angle = 2.0f * PI * i / numSegments;
        float x = radius * cos(angle);
        float z = radius * sin(angle);

        glTexCoord2f(1.0f * i / numSegments, 0.0f);
        glVertex3f(x, -height / 2, z);
        glTexCoord2f(1.0f * i / numSegments, 1.0f);
        glVertex3f(x, height / 2, z);
    }
    glEnd();


}


void Qmosque::drawHcube(GLuint texture, float height, float width, float depth, float r, int numofsegments, float x, float y, float z, float s, float t) {
    float w = 2 * r + 2 * width;
    float h = r + height;
    glPushMatrix();
    glTranslatef(x, y, z);

    drawTexturedCuboid(texture, width, h, depth, r + width / 2, h / 2, z, s, t);
    drawTexturedCuboid(texture, width, h, depth, -(r + width / 2), h / 2, z, s, t);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= numofsegments / 2; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numofsegments);
        float xx = r * cosf(theta);
        float yy = r * sinf(theta);
        float tx = (float)(i * 2) / (numofsegments);
        glTexCoord2f(-tx, 1 - (h - yy) / (h - y));
        glVertex3f(xx, yy, z - (depth / 2));
        glTexCoord2f(-tx, 1.0f);
        glVertex3f(xx, h, z - (depth / 2));

    }
    glEnd();

    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= numofsegments / 2; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numofsegments);
        float xx = r * cosf(theta);
        float yy = r * sinf(theta);
        float tx = (float)(i * 2) / (numofsegments);
        glTexCoord2f(tx, 0.0f);
        glVertex3f(xx, yy, z + (depth / 2));
        glTexCoord2f(tx, 1.0f);
        glVertex3f(xx, h, z + (depth / 2));
    }
    glEnd();

    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= numofsegments / 2; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numofsegments);
        float xx = r * cosf(theta);
        float yy = r * sinf(theta);
        float tx = (float)(i * 2) / (numofsegments);
        glTexCoord2f(tx, 0.0f);
        glVertex3f(xx, yy, z - (depth / 2));
        glTexCoord2f(tx, 1.0f);
        glVertex3f(xx, yy, z + (depth / 2));
    }
    glEnd();

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-r, h, z - depth / 2);
    glTexCoord2f(1, 0);
    glVertex3f(r, h, z - depth / 2);
    glTexCoord2f(1, 1);
    glVertex3f(r, h, z + depth / 2);
    glTexCoord2f(0, 1);
    glVertex3f(-r, h, z + depth / 2);
    glEnd();

    glPopMatrix();
}


void Qmosque::drawBArc(float x, float y, float z, float r, float p, float st, GLuint tex) {
    float numberofpoints = 100;
    glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_QUAD_STRIP);
    for (float i = st; i <= numberofpoints / p + st; i += 0.01) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numberofpoints);
        float ddx = (r + (r * 0.25)) * cosf(theta);
        float ddy = (r + (r * 0.25)) * sinf(theta);
        glTexCoord2f(i * p / numberofpoints, 0);
        glVertex3d(ddx + x, ddy + y, 0 + z);
        glTexCoord2f(i * p / numberofpoints, 1);
        glVertex3d(ddx + x, ddy + y, 0 + z - r + 0.02);
    }
    glEnd();

    glBegin(GL_QUAD_STRIP);
    for (float i = st; i <= numberofpoints / p + st; i += 0.01) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numberofpoints);
        float ddx = (r * cosf(theta));        float ddy = (r * sinf(theta));
        glTexCoord2f(i * p / numberofpoints, 0);
        glVertex3d(ddx + x, ddy + y, 0 + z);
        glTexCoord2f(i * p / numberofpoints, 1);
        glVertex3d(ddx + x, ddy + y, 0 + z - r + 0.02);
    }
    glEnd();
}





void Qmosque::drawArc(float x, float y, float z, float r, float l, float p, float st, GLuint tex) {
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
    glBegin(GL_QUAD_STRIP);
    for (float i = st; i <= numberofpoints / p + st; i += 1) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numberofpoints);
        float dx = r * cosf(theta);
        float dy = r * sinf(theta);
        float ddx = (r + (r * 0.25)) * cosf(theta);
        float ddy = (r + (r * 0.25)) * sinf(theta);
        glTexCoord2f(i * p / numberofpoints, 0); glVertex3d(dx + x, dy + y, z - l);
        glTexCoord2f(i * p / numberofpoints, 1); glVertex3d(ddx + x, ddy + y, z - l);
    }
    glEnd();

    drawBArc(x, y, z, r, p, st, tex);

}


void Qmosque::drawBlockArc(GLuint texture, float radius, float startAngle, float endAngle, int segments, float blockWidth, float blockHeight, float blockDepth) {
    for (int i = 0; i < segments; i++) {
        float angle = startAngle + (endAngle - startAngle) * i / segments;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        drawTexturedCuboid(texture, blockWidth, blockHeight, blockDepth, x, y, 0, 1, 1);
    }
}

void Qmosque::Rect(GLuint texture, float minX, float maxX, float minY, float maxY, float minZ, float maxZ, float s, float t) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (minY == maxY || minZ == maxZ) { ///////// X,Z || X,Y
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(minX, minY, minZ);  // Bottom Left
        glTexCoord2f(s, 0.0f); glVertex3f(maxX, minY, minZ);  // Bottom Right
        glTexCoord2f(s, t); glVertex3f(maxX, maxY, maxZ);  // Top Right
        glTexCoord2f(0.0f, t); glVertex3f(minX, maxY, maxZ);  // Top Left
        glEnd();
    }
    else { /////////Y,Z
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(minX, minY, minZ);  // Bottom Left
        glTexCoord2f(s, 0.0f); glVertex3f(maxX, minY, maxZ);  // Bottom Right
        glTexCoord2f(s, t); glVertex3f(maxX, maxY, maxZ);  // Top Right
        glTexCoord2f(0.0f, t); glVertex3f(minX, maxY, minZ);  // Top Left
        glEnd();
    }

    glDisable(GL_TEXTURE_2D);
}

void Qmosque::drawpolygon(float x, float y, float z, float radius, float length, int numVertices, int tex) {
    const int numVertices1 = 1000;
    float angleIncrement = 2.0f * PI / numVertices;
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
void Qmosque::drawdome(float a, float b, float c, float radius, int tex, int tex1, int sizeofbase) {
    glPushMatrix();
    glTranslatef(0, 0, -5);
    glLineWidth(10.0f);
    //======= Drawing The Crescent =======//
    // Draw the crescent shape using GL_TRIANGLE_FAN
    float numberofpoints = 50;
    glBindTexture(GL_TEXTURE_2D, emam);
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
    glPushMatrix();
    glTranslatef(a, 2 * b - 3, c);
    drawcylinder(roof, 100, 2, radius);
    glPopMatrix();
   /* glBegin(GL_LINES);
    glTexCoord2f(0, 0); glVertex3f(a, radius + b, c);
    glTexCoord2f(1, 1); glVertex3f(a, radius * 2 + b, c);
    glEnd();*/


    //======= Drawing The Base Of The Dome =======//
    if (sizeofbase)
        drawpolygon(a, b - 30, c, radius, 6, 1000, MAINBLOCK);
    //======= Drawing The Main Dome =======//
    glPushMatrix();
    glTranslated(0, b, 0);
    glRotated(90, 1, 0, 0);
    glBindTexture(GL_TEXTURE_2D, roof);
    const int slices = 200;  // Number of horizontal slices
    const int stacks = 100;  // Number of vertical stacks
    for (int i = 0; i < slices / 2; i++) {
        float lat0 = (float)PI * (-0.5f + (float)i / slices);
        float z0 = sin(lat0);
        float zr0 = cos(lat0);

        float lat1 = (float)PI * (-0.5f + (float)(i + 1) / slices);
        float z1 = sin(lat1);
        float zr1 = cos(lat1);
        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= stacks; j++) {
            float lng = (float)2 * PI * (float)j / stacks;
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

void Qmosque::qmosque() {
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
    drawdome(55,40,32, 25 , emam , emam , 10);
    //////////////////////BACK
    Rect(MAINBLOCK, 0, 110, 0, 30, -0.1, -0.1, 11, 3);

    //////////////////////LEFT
    Rect(MAINBLOCK, 0, 0, 0, 30, 33, 160, 14, 3);

    ////////////////////RIGHT
    Rect(MAINBLOCK, 110.1, 110.1, 0, 30, 0, 160, 16, 3);

    /////////////////////infront of the extension
    Rect(MAINBLOCK, 0, 110, 30.1, 30.1, 140, 160, 11, 2);

    ////////////////////DOWN
    Rect(carpet, 0, 110, 0, 0, 0, 140, 11, -14);

    ////////////////////UP(1,2,3)
    Rect(subroof, 0, 41.25, 34, 34, 0, 140, 4.1, 7);

    ////////////////////UP(4)
    Rect(mainroof, 41.25, 68.75, 34, 34, 0, 140, 2.7, 7);

    ////////////////////UP(5)
    Rect(specialroof, 68.75, 82.5, 34, 34, 0, 140, 1.3, 7);

    ////////////////////UP(6,7)
    Rect(subroof, 82.5, 110, 30, 30, 0, 140, 2.7, 7);

    ////////////////////extension

    glPushMatrix();
    drawTexturedCuboid(MAINBLOCK, 110, 4, 2, 55, 32, 159, 11, .5);
    glPopMatrix();

    glPushMatrix();
    drawTexturedCuboid(MAINBLOCK, 27.5, 4, 2, 55, 36, 159, 2.75, .5);
    glPopMatrix();

    /////////////////////SMALL-RIGHT ROOF 1
    Rect(roof, 82.5, 110, 30.1, 30.1, 53.3, 140, 2.7, 8.6);

    /////////////////////SMALL-RIGHT ROOF 2
    Rect(MAINBLOCK, 82.5, 110, 30.1, 30.1, 0, 53.3, 2.7, 5.3);

    /////////////////////DOOR(1-6)

    for (int i = 0; i < 3; i++) {

        Rect(DOORS, 13.75 * i + 2, 13.75 * i + 12, 0, 15, 140, 140, 1, 1);
        Rect(DOORS, 110 - (13.75 * i + 2), 110 - (13.75 * i + 12), 0, 15, 140, 140, 1, 1);

    }

    

    ///infront of the doors
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            float c = 7.5, h = 15;
            glPushMatrix();
            if (i == 0 || i == 3) c = 15, h = 30;
            drawTexturedCuboid(cuboid1, 4, h, 3, 13.75 * i, c, 160 - j * 20, 1, 1);
            drawTexturedCuboid(cuboid1, 4, h, 3, 110 - (13.75 * i), c, 160 - j * 20, 1, 1);
            glPopMatrix();
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            glPushMatrix();
            glTranslatef(13.75 * i + 6.875, 15, 160 - j * 20);
            drawHcube(cuboid1, 10.2, 2.1, 3, 4.8, 100, 0, 0, 0, 1, 1);
            glPopMatrix();
            glPushMatrix();
            glTranslatef(110 - (13.75 * i + 6.875), 15, 160 - j * 20);
            drawHcube(cuboid1, 10.2, 2.1, 3, 4.8, 100, 0, 0, 0, 1, 1);
            glPopMatrix();
        }
    }

    glPushMatrix();
    glTranslatef(55, 15, 140);
    drawHcube(cuboid1, 3.5, 0.5, 3, 11.6, 100, 0, 0, 0, 1, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(55, 15, 160);
    drawHcube(cuboid1, 3.5, 0.5, 3, 11.6, 100, 0, 0, 0, 1, 1);
    glPopMatrix();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// //////////////////////////////////////ROOF 1

    ////////////////////BACK
    Rect(MAINBLOCK, 0, 82.5, 30, 34, 0, 0, 8.2, 0.4);

    ////////////////////FRONT
    Rect(MAINBLOCK, 0, 82.5, 30, 34, 140, 140, 8.2, 0.4);

    ////////////////////LEFT
    Rect(MAINBLOCK, 0, 0, 30, 34, 0, 140, 14, 0.4);

    ////////////////////RIGHT
    Rect(MAINBLOCK, 82.5, 82.5, 30, 34, 0, 140, 14, 0.4);

    ////////////////////UP
    Rect(roof, 0, 82.5, 34.1, 34.1, 0, 140, 8.25, 14);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// ///////////////////////////////////////ROOF 2

    ////////////////////BACK
    Rect(MAINBLOCK, 41.25, 68.75, 34, 40, 53, 53, 2.7, 0.6);

    ////////////////////FRONT
    Rect(MAINBLOCK, 41.25, 68.75, 34, 40, 140, 140, 2.7, 0.6);

    ////////////////////LEFT
    Rect(MAINBLOCK, 41.25, 41.25, 34, 40, 53, 140, 8.7, 0.6);

    ////////////////////RIGHT
    Rect(MAINBLOCK, 68.75, 68.75, 34, 40, 53, 140, 8.7, 0.6);

    ////////////////////UP
    Rect(ROOF2UP, 41.25, 68.75, 40, 40, 53, 140, 2.6, 8.7);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///SIDE THINGS////////////////////////////////////////////////


    ////////////////////BACK
    Rect(MAINBLOCK, -20, 0, 0, 30, 0, 0, 2, 3);

    ////////////////////FRONT
    Rect(MAINBLOCK, -20, 0, 0, 30, 20, 20, 2, 3);

    ////////////////////LEFT
    Rect(MAINBLOCK, -20, -20, 25, 30, 0, 5, 0.5, 0.5);

    ////////////////////LEFT2
    Rect(MAINBLOCK, -20, -20, 25, 30, 15, 20, 0.5, 0.5);

    ////////////////////LEFT3
    Rect(MAINBLOCK, -20, -20, 0, 25, 0, 20, 2, 2.5);

    ///////////////////hole-1st
    Rect(MAINBLOCK, -20, -15, 25, 30, 5, 5, 0.5, 0.5);

    ///////////////////hole-2nd
    Rect(MAINBLOCK, -20, -15, 25, 30, 15, 15, 0.5, 0.5);

    ///////////////////hole-3rd
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, MAINBLOCK);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);

    glTexCoord2f(1, 0);
    glVertex3f(-20, 25, 15);

    glTexCoord2f(0, 0);
    glVertex3f(-20, 25, 5);

    glTexCoord2f(0, 0.5);
    glVertex3f(-15, 25, 5);

    glTexCoord2f(1, 0.5);
    glVertex3f(-15, 25, 15);
    glEnd();

    ///////////////////hole-4th
    Rect(MAINBLOCK, -15, -15, 25, 30, 5, 15, 1, 0.5);

    ////////////////////DOWN
    Rect(carpet, -20, 0, 0, 0, 0, 20, 2, -2);

    ////////////////////UP-1st
    Rect(roof, -15, 0, 30, 30, 0, 20, 1, 2);

    ////////////////////UP-2nd
    Rect(roof, -20, -15, 30, 30, 0, 5, 0.5, 0.5);

    ////////////////////UP-3rd

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, roof);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);

    glTexCoord2f(.5, 0);
    glVertex3f(-15, 30, 20);
    glTexCoord2f(0, 0);
    glVertex3f(-20, 30, 20);
    glTexCoord2f(0, .5);
    glVertex3f(-20, 30, 15);
    glTexCoord2f(.5, .5);
    glVertex3f(-15, 30, 15);
    glEnd();

    ////////////////////BACK2
    Rect(MAINBLOCK, -15, 0, 30, 34, 20, 20, 1.5, 0.4);

    //////////////////////FRONT2
    Rect(MAINBLOCK, -15, 0, 0, 34, 33, 33, 1.5, 3.4);

    //////////////////////LEFT2
    Rect(MAINBLOCK, -15, -15, 0, 34, 20, 33, 1.3, 3.4);

    //////////////////////DOWN2
    Rect(carpet, -15, 0, 0, 0, 20, 33, 1.5, -2);

    //////////////////////UP2
    Rect(roof, -15, 0, 34, 34, 20, 33, 1.5, 1.3);

    //////////////////////FENCE
    glPushMatrix();
    drawTexturedCuboid(fence, 2, 10, 90, -15, 5, 110, 9, 1);
    glPopMatrix();

    //////////////////////PEDESTAL
    for (int i = 0; i < 7; i++) {
        glPushMatrix();
        drawTexturedCuboid(pedestal, 3, 14, 3, -15, 7, 65 + (i * 15), 1, 1);
        glPopMatrix();
    }

    for (int i = 0; i < 5; i++) {

        Rect(window1, -0.2, -0.2, 10, 15, 140 - 15 * i - 9, 140 - 15 * i - 5, 1, 1);
        Rect(window1, -0.2, -0.2, 10, 15, 140 - 15 * i - 15, 140 - 15 * i - 11, 1, 1);

        Rect(window2, -0.2, -0.2, 18, 20, 140 - 15 * i - 10.5, 140 - 15 * i - 9.5, 1, 1);

        Rect(window3, -0.2, -0.2, 28, 31, 140 - 15 * i - 8, 140 - 15 * i - 6, 1, 1);
        Rect(window3, -0.2, -0.2, 28, 31, 140 - 15 * i - 11, 140 - 15 * i - 9, 1, 1);
        Rect(window3, -0.2, -0.2, 28, 31, 140 - 15 * i - 14, 140 - 15 * i - 12, 1, 1);

    }

    for (int i = 1; i <= 5; i++) {

        drawTexturedCuboid(cuboid1, 2, 15, 2, 0, 7.5, 140 - i * 15 - 2.5, 1, 1);
        glPushMatrix();
        glTranslatef(0, 15, 145 - i * 15);
        glRotatef(90, 0, 1, 0);
        drawBlockArc(cuboid1, 7.5, 0, PI, 1000, 2, 1, 2);
        glPopMatrix();
    }


    drawTexturedCuboid(cuboid1, 2, 15, 2, 0, 7.5, 137.5, 1, 1);

    Rect(sidedoor_i, -0.2, -0.2, 1, 20, 44, 54, 1, 1);


    glPushMatrix();
    glTranslatef(-0.2, 20, 49);
    glRotatef(90, 0, 1, 0);
    drawTexturedCuboid(pedestal, 6, 20, 0.5, 8, -10, 0, 1, 1);
    drawTexturedCuboid(pedestal, 6, 20, 0.5, -8, -10, 0, 1, 1);
    drawTexturedCuboid(pedestal, 22, 1, 5, 0, -19.5, -2.5, 1, 1);

    drawHcube(pedestal, 4, 6, 0.5, 5, 100, 0, 0, 0, 1, 1);
    glPopMatrix();
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///THE INSIDE///////////////////////////////////////////////////////////

    //////////////////////EMAM
    Rect(emam, 55 - 10, 55 + 10, 0, 30, 0.2, 0.2, 1, 1);

    //////////////////////BACK-inside
    Rect(inside, 0, 110, 0, 30, 0.1, 0.1, 11, 3);

    //////////////////////LEFT-inside
    Rect(inside, 0.1, 0.1, 0, 30, 33, 160, 14, 3);

    ////////////////////RIGHT-inside
    Rect(inside, 109.9, 109.9, 0, 30, 0, 160, 16, 3);

    ////////////////////MIDDLE
    Rect(inside, -14.9, -14.9, 0, 30, 0, 20, 2, 3);


    ///roof1-inside ///////////////
    ////////////////////BACK-inside
    Rect(inside, 0, 82.5, 30, 34, 0.1, 0.1, 8.25, 0.4);

    ////////////////////FRONT-inside
    Rect(inside, 0, 82.5, 30, 34, 139.9, 139.9, 8.25, 0.4);

    ////////////////////LEFT-inside
    Rect(inside, 0.1, 0.1, 30, 34, 0, 139.9, 13.9, 0.4);

    /// ////////////////////////////////////side-inside

    ////////////////////BACK-inside
    Rect(inside, -20, 0, 0, 30, 0.1, 0.1, 2, 3);

    ////////////////////FRONT-inside
    Rect(inside, -20, 0, 0, 30, 18, 18, 2, 3);

    ////////////////////BACK2-inside
    Rect(inside, -15, 0, 0, 34, 21, 21, 1.5, 3);

    ////////////////////BETWEEN-inside
    Rect(inside, 0, 0, 0, 34, 18, 21, 0.3, 3.4);

    //////////////////////LEFT2-inside
    Rect(inside, -14.9, -14.9, 0, 34, 20, 33, 1.3, 3.4);

    ////////////////////FRONT2-inside
    Rect(inside, -15, 0, 0, 34, 32.9, 32.9, 1.5, 3);


    for (int i = 0; i < 5; i++) {

        Rect(window1, 0.2, 0.2, 10, 15, 140 - 15 * i - 9, 140 - 15 * i - 5, 1, 1);
        Rect(window1, 0.2, 0.2, 10, 15, 140 - 15 * i - 15, 140 - 15 * i - 11, 1, 1);

        Rect(window2, 0.2, 0.2, 18, 20, 140 - 15 * i - 10.5, 140 - 15 * i - 9.5, 1, 1);

        Rect(window3, 0.2, 0.2, 28, 31, 140 - 15 * i - 8, 140 - 15 * i - 6, 1, 1);
        Rect(window3, 0.2, 0.2, 28, 31, 140 - 15 * i - 11, 140 - 15 * i - 9, 1, 1);
        Rect(window3, 0.2, 0.2, 28, 31, 140 - 15 * i - 14, 140 - 15 * i - 12, 1, 1);

    }

    Rect(sidedoor_i, 0.2, 0.2, 1, 20, 44, 54, 1, 1);

    ///////////////////////////////////////////
    for (int i = 1; i <= 6; i++) {
        for (int j = 1; j <= 4; j++) {
            glPushMatrix();
            glTranslatef(j * 13.75, 7.51, 140 - 15 * i);
            if (i != 6) glTranslatef(0, 0, -2.5);
            if (j == 4) glTranslatef(13.75, 0, 0);
            drawcylinder(cylinder1, 1000, 1, 15);
            drawTexturedCuboid(cylinder1, 2, 1, 2, 0, -15 / 2, 0, 1, 1);
            glPopMatrix();

        }
    }
    for (int i = 1; i <= 7; i++) {
        for (int j = 1; j <= 3; j++) {
            glPushMatrix();
            if (i < 6) glTranslatef(0, 0, -2.5);
            glTranslatef(68.75 + j * 13.75, 7.51, 140 - 15 * i);
            drawTexturedCuboid(cuboid1, 2, 15, 2, 0, 0, 0, 1, 1);
            glPopMatrix();

        }
    }

    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 2; j++) {
            glPushMatrix();
            glTranslatef(68.75 + j * 13.75, 7.51, 8 * i);
            drawcylinder(cylinder2, 1000, 1, 15);
            drawTexturedCuboid(cylinder2, 2, 1, 2, 0, -15 / 2, 0, 1, 1);
            glPopMatrix();

        }
    }

    for (int i = 1; i <= 2; i++) {
        for (int j = 1; j <= 2; j++) {
            glPushMatrix();
            glTranslatef(j * 13.75, 7.51, 8 + 8 * i);
            drawcylinder(cylinder2, 1000, 1, 15);
            drawTexturedCuboid(cylinder2, 2, 1, 2, 0, -15 / 2, 0, 1, 1);
            glPopMatrix();

        }
    }

    int c = 0;
    for (int i = 0; i <= 1; i++) {
        for (int j = 1; j <= 2; j++) {
            if (i == 1 && j == 1) c = 90;
            if (i == 1 && j == 2) c += 180;
            glPushMatrix();
            glTranslatef(13.75 + j * 27.5, 7.51, 8 + 27 * i);
            glPushMatrix();
            glRotatef(c, 0, 1, 0);
            glPushMatrix();
            glTranslatef(2, 0, 0);
            drawcylinder(cylinder3, 100, 1, 15);
            glPopMatrix();
            glPushMatrix();
            glTranslatef(0, 0, 2);
            drawcylinder(cylinder3, 100, 1, 15);
            glPopMatrix();
            drawTexturedCuboid(cuboid3, 2, 15, 2, 0, 0, 0, 1, 1);
            glPopMatrix();
            glPopMatrix();
            c -= 90;
        }
    }

    for (int i = 0; i <= 1; i++) {
        for (int j = 1; j <= 2; j++) {
            glPushMatrix();
            glTranslatef(j * 13.75, 7.51, 8 + 27 * i);
            if (i == 1) {
                glPushMatrix();
                glTranslatef(0, .1, 2);
                drawcylinder(cylinder2, 1000, 1, 15);
                drawTexturedCuboid(cylinder2, 2, 1, 2, 0, -15 / 2, 0, 1, 1);
                glPopMatrix();
            }
            drawTexturedCuboid(cuboid2, 2, 15, 2, 0, 0, 0, 1, 2);
            glPopMatrix();

        }
    }
    /// VERTICAL/////////
    for (int i = 1; i <= 7; i++) {
        for (int j = 1; j <= 4; j++) {
            float h = 12.5;
            if (i == 4)continue;
            if (i == 7) h = 8.5;
            glPushMatrix();
            glTranslatef(13.75 * i, 15, 140 - j * 15 - 10);
            glRotatef(90, 0, 1, 0);
            drawHcube(inside, h, 1, 2, 6.5, 100, 0, 0, 0, 1, 1);
            glPopMatrix();
        }
    }

    for (int i = 1; i <= 7; i++) {
        float h = 16;
        if (i >= 3 && i <= 5) continue;
        if (i == 7) h = 12;
        glPushMatrix();
        glTranslatef(13.75 * i, 15, 4);
        glRotatef(90, 0, 1, 0);
        drawHcube(inside, h, 1, 2, 3, 100, 0, 0, 0, 1, 1);
        glPushMatrix();
        glTranslatef(4, -7.5, 0);
        drawTexturedCuboid(cuboid1, 2, 15, 2, 0, 0, 0, 1, 1.5);
        glPopMatrix();
        glPopMatrix();
    }

    for (int i = 1; i <= 7; i++) {
        float h = 11.5;
        if (i == 4)continue;
        if (i == 7) h = 7.5;
        glPushMatrix();
        glTranslatef(13.75 * i, 15, 131);
        glRotatef(90, 0, 1, 0);
        drawHcube(inside, h, 1, 2, 7.5, 100, 0, 0, 0, 1, 1);
        glPopMatrix();
    }

    for (int i = 1; i <= 7; i++) {
        float h = 13.75;
        if (i == 4)continue;
        if (i == 7) h = 9.75;
        glPushMatrix();
        glTranslatef(13.75 * i, 15, 56.25);
        glRotatef(90, 0, 1, 0);
        drawHcube(inside, h, 1, 2, 5.25, 100, 0, 0, 0, 1, 1);
        glPopMatrix();
    }
    for (int i = 1; i <= 7; i++) {
        float h = 16;
        if (i == 7) h = 12;
        if (i >= 3 && i <= 5) continue;
        glPushMatrix();
        glTranslatef(13.75 * i, 15, 12);
        glRotatef(90, 0, 1, 0);
        drawHcube(inside, h, 1, 2, 3, 100, 0, 0, 0, 1, 1);
        glPopMatrix();
    }

    for (int i = 1; i <= 7; i++) {
        float h = 14.5;
        if (i == 7) h = 10.5;
        if (i >= 3 && i <= 5) continue;
        glPushMatrix();
        glTranslatef(13.75 * i, 15, 29.5);
        glRotatef(90, 0, 1, 0);
        drawHcube(inside, h, 1, 2, 4.5, 100, 0, 0, 0, 1, 1);
        glPopMatrix();
    }

    for (int i = 1; i <= 7; i++) {
        float h = 12.5;
        if (i == 7) h = 8.5;
        if (i == 4) continue;
        glPushMatrix();
        glTranslatef(13.75 * i, 15, 42.5);
        glRotatef(90, 0, 1, 0);
        drawHcube(inside, h, 1, 2, 6.5, 100, 0, 0, 0, 1, 1);
        glPopMatrix();
    }

    for (int i = 1; i <= 7; i++) {
        float h = 16;
        if (i == 3 || i == 4 || i == 5)continue;
        if (i == 7) h = 12;
        glPushMatrix();
        glTranslatef(13.75 * i, 15, 20);
        glRotatef(90, 0, 1, 0);
        drawHcube(inside, h, 1, 2, 3, 100, 0, 0, 0, 1, 1);
        glPopMatrix();
    }

    /// HORIZONTAL/////////

    for (int i = 1; i < 8; i++) {
        for (int j = 0; j <= 1; j++) {
            float h = 9, dis = 0;
            glPushMatrix();
            if (i >= 6) dis = 2.5;
            glTranslatef(110 - 13.75 * j - 6.875, 15, 140 - i * 15 - 2.5 + dis);
            drawHcube(inside, h, 1, 2, 5.875, 100, 0, 0, 0, 1, 1);
            glPopMatrix();
        }
    }
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            glPushMatrix();
            glTranslatef(20.625 + 13.75 * j, 15, 8 + 27 * i);
            drawHcube(inside, 13.1, 1, 2, 5.875, 100, 0, 0, 0, 1, 1);
            glPopMatrix();
        }
    }
    glPushMatrix();
    glTranslatef(68.75 + 6.875, 15, 8);
    drawHcube(inside, 13.1, 1, 2, 5.875, 100, 0, 0, 0, 1, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(68.75 + 20.625, 15, 8);
    drawHcube(inside, 9.1, 1, 2, 5.875, 100, 0, 0, 0, 1, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(68.75 + 6.875, 15, 8 + 27);
    drawHcube(inside, 13.1, 1, 2, 5.875, 100, 0, 0, 0, 1, 1);
    glPopMatrix();

    /// /// MAIN ARCS//////
    ////////BACK
    glPushMatrix();
    glTranslatef(55, 15, 9);
    drawHcube(cylinder3, 8, 4, 4, 10.75, 100, 0, 0, 0, 1, 1);
    glPopMatrix();

    ////////FRONT
    glPushMatrix();
    glTranslatef(55, 15, 8 + 26);
    drawHcube(cylinder3, 8, 4, 4, 10.75, 100, 0, 0, 0, 1, 1);
    glPopMatrix();

    ////////RIGHT
    glPushMatrix();
    glTranslatef(67.75, 15, 21.5);
    glRotatef(90, 0, 1, 0);
    drawHcube(cylinder3, 8, 4, 4, 10.5, 100, 0, 0, 0, 1, 1);
    glPopMatrix();

    ////////LEFT
    glPushMatrix();
    glTranslatef(42.25, 15, 21.5);
    glRotatef(90, 0, 1, 0);
    drawHcube(cylinder3, 8, 4, 4, 10.5, 100, 0, 0, 0, 1, 1);
    glPopMatrix();
    ///above the doors

    glPushMatrix();
    drawTexturedCuboid(glass, 109.9, 15, 2, 55, 22.5, 140, 11, 1);
    glPopMatrix();

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
