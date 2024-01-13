#include <Windows.h>
#include <winreg.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include "texture.h"
#include <math.h>
#include <GLAUX.H>
#include "Model_3DS.h"
#include <vector>
#include <map>
#include <mmsystem.h>
#include "DomeOfRock.h"
#include "Building.h"
#include "MosqueSquare.h"
#include "Camera.h"
#include "Qmosque.h"

#pragma comment(lib, "AdvAPI32.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")
#pragma comment(lib, "winmm.lib")
using namespace std;
#define M_PI 3.14159265358979323846
//==========================================//
//              Parameters                  //
// Global
Camera camera(glm::vec3(-591.581f ,  0 ,  2158.51f));
bool firstMouse = true;
float lastX = 1920.0f / 2.0;
float lastY = 1080.0f / 2.0;
// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

Model_3DS* tree;
Model_3DS* flag;

GLTexture BARK, Leaf,Flag , t1 ,t2;
int FLAG , FLAG2; 

struct Point {
    float x, y;
};

const int slices = 200;  // Number of horizontal slices
const int stacks = 100;  // Number of vertical stacks
// skybox
int SKYFRONT, SKYBACK, SKYLEFT, SKYRIGHT, SKYUP, SKYDOWN , night;
// Character
int frontleg, backleg, frontface, backface, hand, sideface, frontbody, backbody;
// dome

int dome , dome1 , dome3 , dome4 , dome5;
int H;
int ww = 1920;
int hh = 1080;
bool stsound = 1;
map<string, int> domeOfRockTex;

map<string, int> buildingTex;
Building buildings;
Wall generalWall;

MosqueSquare square;
Qmosque* qmosque;
GLuint domeDisplayList;
float a , b;

double vertices[8][3] = {
    { -2 ,  -2  ,  +9 },  // 0
    { +2 ,  -2  ,  +9}, // 1
    { +2 ,  +2  ,  +9 },   // 2
    { -2 ,  +2  ,  +9 },  // 3
    { -2 ,  -2  ,  +12},   // 4
    { +2 ,  -2  ,  +12 },   // 5
    { +2 ,  +2  ,  +12 },   // 6
    { -2 ,  +2  ,  +12 }  // 7
};
// Define the indices for the faces of the cube
int faces[6][4] = {
    { 0, 1, 2, 3 }, // front face
    { 1, 5, 6, 2 }, // right face
    { 4, 5, 6, 7 }, // back face
    { 0, 4, 7, 3 }, // left face
    { 3, 2, 6, 7 }, // top face
    { 4, 5, 1, 0 }  // bottom face
};
Point TexCoor[4] = { {0,0} , {1,0} , {1,1} , {0,1} };
GLfloat LightDir[] = { 0.0f,0.0f,0.0f,1.0f };
GLfloat LightPos[] = { 0.0f,-300.0f,3.0f,1.0f };

GLfloat LightAmb[] = { 0.5,0.5f,0.5f,1.0f };
GLfloat LightDiff[] = { 100.0f,100.0f,100.0f,1.0f };
GLfloat LightSpec[] = { 100.0f,100.0f,100.0f,1.0f };


GLfloat MatAmb[] = { 0,0,0,1.0f };
GLfloat MatDif[] = { 0,0,0,1.0f };
GLfloat MatSpec[] = { 0,0,0,1.0f };

GLfloat MatShn[] = { 300.0f };
// TPS 
float TPSy = 0, TPSz = 0;
int stone , stone1 , QaytBayfront , QaytBayside , arc , arc1 , arc2 , marble , marble1 , marble2 , marble3, decor1 , decor2 , decor3, decor4 , decor5 , decor6 , decor7;
int floor1,wood , frontwall , leftfrontwall,door,soor , wallout , roof , ground2;
int carpet;
int grass, grass2, wall, demoAlshekWall, demoAlshek, demoAlshekFace, demoWall, demoWallFace , v1,v2;
int hello2, door2, s;
int domeMousa, domeMousaFace, domeMousaRoof, domeMousaq, domeMousaBottomDome , yossef , sun;
bool nightt = 0 , onground = 1 , ondome = 0;
int TEX;
//==========================================//

bool check(float x, float y, float z) {
    if (x > 5452.64 || z < -5467.01 || x < -5458.54 || z > 5337.65)return 0;
    if (x <= 1010 && x >= -980 && y < -150 && z <= 1420 && z >= -640)return 0;
    if (y <= -240)return 0;
    return 1;
}

void mouse_callback(int xposIn, int yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;
    camera.ProcessMouseMovement(xoffset, yoffset);

}
void processNormalKeys(unsigned char key, int x, int y) {
    if (key == 27) // the Esc key
        exit(0);

    float cameraSpeed = static_cast<float>(0.05 * deltaTime);
    if (key == 'w' || key == 'W') {
        if (check(camera.Position.x + cameraSpeed * camera.Front.x, camera.Position.y + cameraSpeed * camera.Front.y, camera.Position.z + cameraSpeed * camera.Front.z))
            camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (key == 's' || key == 'S') {
        if (check(camera.Position.x - cameraSpeed * camera.Front.x, camera.Position.y - cameraSpeed * camera.Front.y, camera.Position.z - cameraSpeed * camera.Front.z))
            camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (key == 'a' || key == 'A') {
        if (check(camera.Position.x - cameraSpeed * camera.Right.x, camera.Position.y - cameraSpeed * camera.Right.y, camera.Position.z - cameraSpeed * camera.Right.z))
            camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (key == 'd' || key == 'D') {
        if (check(camera.Position.x + cameraSpeed * camera.Right.x, camera.Position.y + cameraSpeed * camera.Right.y, camera.Position.z + cameraSpeed * camera.Right.z))
            camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    if (key == 'l' || key == 'L') {
        if (check(camera.Position.x + cameraSpeed * camera.Up.x, camera.Position.y + cameraSpeed * camera.Up.y, camera.Position.z + cameraSpeed * camera.Up.z))
            camera.ProcessKeyboard(UP, deltaTime);
    }
    if (key == 'k' || key == 'K') {
        if (check(camera.Position.x - cameraSpeed * camera.Up.x, camera.Position.y - cameraSpeed * camera.Up.y, camera.Position.z - cameraSpeed * camera.Up.z))
            camera.Position -= cameraSpeed * camera.Up;
    }
    if (key == 'p' || key == 'P')
        camera.TPSy = 3, camera.TPSz = 1;
    if (key == 'u' || key == 'U') {
        cout << camera.Position.x << " " << camera.Position.y << " " << camera.Position.z << '\n';
        camera.TPSy = camera.TPSz = 0;
    }
    if (key == 'n' || key == 'N') {
        nightt = !nightt;
        if (nightt)TEX = marble;
        else TEX = sun;
        cout << nightt << "\n";
    }
    if(key == 'z' || key == 'Z') {
        onground = !onground;
    }
    if (key == 'q' || key == 'Q') {
        ondome = !ondome;
    }
    if (key == 'f' || key == 'F') {
        b -= 15;
        a = 0;
    }
    if (key == 'g' || key == 'G') {
        b += 15;
        a = 10;
    }
}
void processSpecialKeys(int key, int x, int y) {
    float xyaw = 0, ypitch = 9;
    if (key == GLUT_KEY_UP) {
        camera.Pitch += (3);
    }
    if (key == GLUT_KEY_DOWN) {
        camera.Pitch += (-3);
    }
    if (key == GLUT_KEY_LEFT) {
        camera.Yaw += (-3);
    }
    if (key == GLUT_KEY_RIGHT) {
        camera.Yaw += (3);
    }
    if (camera.Pitch > 89.0f)
        camera.Pitch = 89.0f;
    if (camera.Pitch < -89.0f)
        camera.Pitch = -89.0f;
    camera.updateCameraVectors();
}
void Camera1() {
    glm::vec3 sight = camera.Position + camera.Front;
    gluLookAt(camera.Position.x, camera.Position.y + camera.TPSy, camera.Position.z + camera.TPSz, sight.x, sight.y + camera.TPSy, sight.z + camera.TPSz, camera.Up.x, camera.Up.y, camera.Up.z);
}
void drawpolygon(float x, float y, float z, float radius, float length, int numVertices, int tex) {
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
void drawdome(float a, float b , float c , float radius ,  int tex , int tex1 , int sizeofbase) {

    glLineWidth(10.0f);
    //======= Drawing The Crescent =======//
    // Draw the crescent shape using GL_TRIANGLE_FAN
    float numberofpoints = 50;
    glBindTexture(GL_TEXTURE_2D, marble);
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
    glTexCoord2f(0,0); glVertex3f(a, radius + b, c);
    glTexCoord2f(1, 1); glVertex3f(a, radius * 2 + b, c);
    glEnd();


    //======= Drawing The Base Of The Dome =======//
    if(sizeofbase)
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
            glVertex3f(x * zr0 * radius + a, y * zr0 * radius + c, z0 * radius );
            glTexCoord2f((float)j * 2 / stacks, (float)(i + 1) * 2 / slices);
            glVertex3f(x * zr1 * radius + a, y * zr1 * radius + c, z1 * radius );
        }
        glEnd();
    }
    glPopMatrix();
}
void Draw_Skybox(float x, float y, float z, float width, float height, float length, int front, int back, int left, int right, int up, int down)
{
    float add = ((front == ground2) ? 50 : 0);
    // Center the Skybox around the given x,y,z position
    x = x - width / 2;
    y = y - height / 2;
    z = z - length / 2;
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    // Draw Front side
    glBindTexture(GL_TEXTURE_2D, front);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f + add, 0.0f); glVertex3f(x, y, z + length);
    glTexCoord2f(1.0f + add, 1.0f + add); glVertex3f(x, y + height, z + length);
    glTexCoord2f(0.0f, 1.0f + add); glVertex3f(x + width, y + height, z + length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);
    glEnd();

    // Draw Back side
    glBindTexture(GL_TEXTURE_2D, back);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f + add, 0.0f); glVertex3f(x + width, y, z);
    glTexCoord2f(1.0f + add, 1.0f + add); glVertex3f(x + width, y + height, z);
    glTexCoord2f(0.0f, 1.0f + add); glVertex3f(x, y + height, z);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
    glEnd();

    // Draw Left side
    glBindTexture(GL_TEXTURE_2D, left);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f + add, 1.0f + add); glVertex3f(x, y + height, z);
    glTexCoord2f(0.0f, 1.0f + add); glVertex3f(x, y + height, z + length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
    glTexCoord2f(1.0f + add, 0.0f); glVertex3f(x, y, z);
    glEnd();

    // Draw Right side
    glBindTexture(GL_TEXTURE_2D, right);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
    glTexCoord2f(1.0f + add, 0.0f); glVertex3f(x + width, y, z + length);
    glTexCoord2f(1.0f + add, 1.0f + add); glVertex3f(x + width, y + height, z + length);
    glTexCoord2f(0.0f, 1.0f + add); glVertex3f(x + width, y + height, z);
    glEnd();

    // Draw Up side
    glBindTexture(GL_TEXTURE_2D, up);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z);
    glTexCoord2f(1.0f + add, 0.0f); glVertex3f(x + width, y + height, z + length);
    glTexCoord2f(1.0f + add, 1.0f + add); glVertex3f(x, y + height, z + length);
    glTexCoord2f(0.0f, 1.0f + add); glVertex3f(x, y + height, z);
    glEnd();

    // Draw Down side
    glBindTexture(GL_TEXTURE_2D, down);


    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
    glTexCoord2f(1.0f + add, 0.0f); glVertex3f(x, y, z + length);
    glTexCoord2f(1.0f + add, 1.0f + add); glVertex3f(x + width, y, z + length);
    glTexCoord2f(0.0f, 1.0f + add); glVertex3f(x + width, y, z);
    glEnd();

    glColor3f(1, 1, 1);

}
// ===================================== //

void drawCharacter() {
    glPushMatrix();
    glTranslated(cos(glm::radians(camera.Yaw)) * camera.TPSz + camera.Position.x, camera.Position.y, sin(glm::radians(camera.Yaw)) * camera.TPSz + camera.TPSz + camera.Position.z);
    glRotated((-camera.Yaw - 90), 0, 1, 0);
    glEnable(GL_TEXTURE_2D);
    glm::vec3 sight = camera.Position + camera.Front;
    float scale = 0.0f;
    int tex = 0;
    // Head
    glPushMatrix();
    // make it smaller
    glScaled(0.3f, 0.3f, 0.3f);
    scale = 0.3f;
    for (int i = 0; i < 6; i++) {
        if (i == 1 || i == 3)tex = sideface;
        else if (i == 0)tex = frontface;
        else tex = backface;
        glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_QUADS);
        for (int j = 0; j < 4; j++) {
            double POS[3] = { vertices[faces[i][j]][0] , vertices[faces[i][j]][1] , vertices[faces[i][j]][2] };
            glTexCoord2d(TexCoor[j].x, TexCoor[j].y);
            glVertex3dv(POS);
        }
    glEnd();
    }
    glPopMatrix();
    // Body
    glPushMatrix();
    glScaled(0.6f, 0.6f, 0.6f);
    glTranslated(0, -3, -5);
    scale = .6f;
    for (int i = 0; i < 6; i++) {
        if (i == 0)tex = frontbody;
        else tex = backbody;
        glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_QUADS);
        for (int j = 0; j < 4; j++) {
            double POS[3] = { vertices[faces[i][j]][0]  + ((vertices[faces[i][j]][0]  == -2) ? 1 : -1),vertices[faces[i][j]][1] , vertices[faces[i][j]][2] + ((faces[i][j] < 4) ? 1 : -1)};
            glTexCoord2d(TexCoor[j].x, TexCoor[j].y);
            glVertex3dv(POS);                                   
        }                                                       
    glEnd();                                                    
    }                                                           
    glPopMatrix();                                              
                                                                
    tex = hand;                                                 
    glBindTexture(GL_TEXTURE_2D, tex);                          
    // right hand                                               
    glPushMatrix();                                             
    glScaled(0.1f, 0.1f, 0.1f);                                 
    glTranslated(7, -8, 22);                                    
    scale = .1f;                                                
    for (int i = 0; i < 6; i++) {                               
    glBegin(GL_QUADS);                                          
        for (int j = 0; j < 4; j++) {
            double POS[3] = { vertices[faces[i][j]][0]  ,vertices[faces[i][j]][1]+ ((faces[i][j] != 2 && faces[i][j] != 3 && faces[i][j] != 6 && faces[i][j] != 7) ? -9 : 0), vertices[faces[i][j]][2] };
            glTexCoord2d(TexCoor[j].x, TexCoor[j].y);
            glVertex3dv(POS);
        }
    glEnd();
    }
    glPopMatrix();


   
    // left hand
    glPushMatrix();
    glScaled(0.1f, 0.1f, 0.1f);
    glTranslated(-7, -8, 22);
    
    scale = .1f;
    for (int i = 0; i < 6; i++) {
    glBegin(GL_QUADS);
        for (int j = 0; j < 4; j++) {
            double POS[3] = { vertices[faces[i][j]][0] ,vertices[faces[i][j]][1] + ((faces[i][j] != 2 && faces[i][j] != 3 && faces[i][j] != 6 && faces[i][j] != 7) ? -9 : 0), vertices[faces[i][j]][2]  };
            glTexCoord2d(TexCoor[j].x, TexCoor[j].y);
            glVertex3dv(POS);
        }
    glEnd();
    }
    if(!onground && !ondome){
    glBindTexture(GL_TEXTURE_2D, marble);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3d(-2 , -11, 9 );
    glTexCoord2f(1, 0); glVertex3d(0 , -11 , 9 );
    glTexCoord2f(1, 1); glVertex3d(0 , 16 , 9 );
    glTexCoord2f(0, 1); glVertex3d(-2, 16 , 9);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, FLAG);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3d(-2 ,16 , 9 );
    glTexCoord2f(1, 0); glVertex3d(16 , 16 , 9 );
    glTexCoord2f(1, 1); glVertex3d(16 , 32, 9 );
    glTexCoord2f(0, 1); glVertex3d(-2, 32, 9 );
    glEnd();
    }
    glPopMatrix();


    // left Leg
    glPushMatrix();
    glScaled(0.1f, 0.1f, 0.1f);
    glTranslated(4, -32, 22);
    scale = .1f;
    for (int i = 0; i < 6; i++) {
        if (i == 0)tex = frontleg;
        else tex = backleg;
        glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_QUADS);
        for (int j = 0; j < 4; j++) {
            double POS[3] = { vertices[faces[i][j]][0] ,vertices[faces[i][j]][1]  + ((faces[i][j] != 2 && faces[i][j] != 3 && faces[i][j] != 6 && faces[i][j] != 7) ? -9 : 0), vertices[faces[i][j]][2] };
            glTexCoord2d(TexCoor[j].x, TexCoor[j].y);
            glVertex3dv(POS);
        }
    glEnd();
    }
    glPopMatrix();

    // right Leg
    glPushMatrix();
    glScaled(0.1f, 0.1f, 0.1f);
    glTranslated(-4, -32, 22);
    scale = .1f;
    for (int i = 0; i < 6; i++) {
        if (i == 0)tex = frontleg;
        else tex = backleg;
        glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_QUADS);
        for (int j = 0; j < 4; j++) {
            double POS[3] = { vertices[faces[i][j]][0]  ,vertices[faces[i][j]][1]  + ((faces[i][j] != 2 && faces[i][j] != 3 && faces[i][j] != 6 && faces[i][j] != 7) ? -9 : 0), vertices[faces[i][j]][2]  };
            glTexCoord2d(TexCoor[j].x, TexCoor[j].y);
            glVertex3dv(POS);
        }
    glEnd();
    }
    glPopMatrix();

    glPopMatrix();
}
void drawsmthn(float x, float y, float z, float r, float width) {
    float a = 0, stepa = 10;
    glPushMatrix();
    glTranslated(x, y, z);
    glRotated(90, 1, 0, 0);
    for (a = 0; a < 40; a += 1) {

        float x = r * cos(a);
        float z = r * sin(a);


        glBegin(GL_QUADS);

        glVertex3f(x, 0, z);
        glVertex3f(r * cos(a + stepa), 0, r * sin(a + stepa));
        glVertex3f(r * cos(a + stepa), width, r * sin(a + stepa));
        glVertex3f(x, width, z);

        glEnd();
    }
    glPopMatrix();
}
void drawCube(float x, float y, float z, int tex) {
    for (int i = 0; i < 6; i++) {
        if(i == 4)
        glBindTexture(GL_TEXTURE_2D, tex);
        else 
            glBindTexture(GL_TEXTURE_2D, stone);
        glBegin(GL_QUADS);
        for (int j = 0; j < 4; j++) {
            float addx = ((faces[i][j] == 1 || faces[i][j] == 2 || faces[i][j] == 5 || faces[i][j] == 6) ? 300 : -300);
            float addy = ((faces[i][j] == 2 || faces[i][j] == 3 || faces[i][j] == 6 || faces[i][j] == 7) ? 50 : -50);
            float addz = ((faces[i][j] <= 3) ? 300 : -300);
            double POS[3] = { vertices[faces[i][j]][0] + x + addx ,vertices[faces[i][j]][1] + y + addy , vertices[faces[i][j]][2] + z + addz};
            glTexCoord2d(TexCoor[j].x, TexCoor[j].y);
            glVertex3dv(POS);
        }
        glEnd();
    }
    tree->pos.x = x;
    tree->pos.y = y;
    tree->pos.z = z;
    tree->Draw();
}
void drawCircStaircase(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(-1.0, 0, 0);
    float r = 1.0f;
    float numberofpoints = 100;
    float dify = 0.5;
    float difz = 0;
    for (int ii = 0; ii < 4; ii++) {
        glBegin(GL_QUAD_STRIP);
        for (float i = 0; i < numberofpoints / 2; i += 0.01)
        {
            float theta = 2.0f * 3.1415926f * float(i) / numberofpoints;
            float dx = r * cosf(theta);
            float dy = r * sinf(theta);
            glTexCoord2d(float(ii / 4.0f), float(i * 2 / numberofpoints)); glVertex3f(dx + x, y + dify, -dy + z);
            glTexCoord2d(float((ii + 1) / 4.0f), float(i * 2 / numberofpoints)); glVertex3f(dx + x, y + dify + 0.5, -dy + z);

        }
        glEnd();
        glBegin(GL_QUAD_STRIP);
        for (float i = 0; i < numberofpoints / 2; i += 0.01)
        {
            float theta = 2.0f * 3.1415926f * float(i) / numberofpoints;
            float dx = r * cosf(theta);
            float dy = r * sinf(theta);
            glTexCoord2d(float(ii / 4.0f), float(i * 2 / numberofpoints));
            glVertex3f(dx + x, y + dify + 0.5, -dy + z);
            theta = 2.0f * 3.1415926f * float(100.0f / 2.0f - i) / numberofpoints;
            dx = r * cosf(theta);
            dy = r * sinf(theta);
            glTexCoord2d(float((ii + 1) / 4.0f), float(i * 2 / numberofpoints));
            glVertex3f(dx + x, y + dify + 0.5, -dy + z);
        }
        glEnd();
        dify -= 0.5;
        r += 0.5;
    }
    glPopMatrix();
}
void drawQaytBay(float x, float y, float z, float lengthx,float lengthy, float lengthz) {
    glPushMatrix();
    glTranslatef(100, 0, 0);
    Stair leftStair(x , y , z , lengthx , lengthy,lengthz , 1,stone1);
    Stair rightStair(x, y, z, lengthx, lengthy, lengthz, 3,stone1);
    drawCircStaircase(x, y, z);

    // Draw Body
    glPushMatrix();
    glTranslatef(0, 3.0f, -9.0f);
    int tex = stone;
    for (int i = 0; i < 6; i++) {
        if (i == 0)tex = QaytBayfront;
        
        glBindTexture(GL_TEXTURE_2D, tex);
        glBegin(GL_QUADS);
        for (int j = 0; j < 4; j++) {
            float addx = 0;
            float addy = 0;
            float addz = 0;
            if (faces[i][j] == 0 || faces[i][j] == 3 || faces[i][j] == 4 || faces[i][j] == 7)addx = -2;
            else addx = 4;
            if (faces[i][j] == 2 || faces[i][j] == 3 || faces[i][j] == 6 || faces[i][j] == 7)addy = 4;
            if (faces[i][j] >= 4)addz = 6;
            double POS[3] = { vertices[faces[i][j]][0] + x + addx ,vertices[faces[i][j]][1] + y + addy, vertices[faces[i][j]][2] + z + addz };
            glTexCoord2d(TexCoor[j].x, TexCoor[j].y);
            glVertex3dv(POS);
        }
        glEnd();
    }
    glPopMatrix();
    
    
    // Draw Base
    glPushMatrix();
    glTranslatef(0, 1.0f, -9.0f);
    glBindTexture(GL_TEXTURE_2D, stone1);
    for (int i = 0; i < 6; i++) {
        glBegin(GL_QUADS);
        for (int j = 0; j < 4; j++) {
            float addx = 0;
            float addy = 0;
            float addz = 0;
            if (faces[i][j] == 0 || faces[i][j] == 3 || faces[i][j] == 4 || faces[i][j] == 7)addx = -2;
            else addx = 4;
            if (faces[i][j] == 2 || faces[i][j] == 3 || faces[i][j] == 6 || faces[i][j] == 7)addy = -2;
            if (faces[i][j] >= 4)addz = 6;
            double POS[3] = { vertices[faces[i][j]][0] + x + addx ,vertices[faces[i][j]][1] + y + addy, vertices[faces[i][j]][2] + z + addz };
            glTexCoord2d(TexCoor[j].x, TexCoor[j].y);
            glVertex3dv(POS);
        }
        glEnd();
    }
    glPopMatrix();
    

    glPushMatrix();
    glTranslatef(-20, 13, -5);
    drawdome(0, 15, 10, 3, dome1, dome1 , 400);
    glPopMatrix();

    glPopMatrix();

}


void drawArc(float x, float y, float z, float r , float p,float st , int tex) {
    float numberofpoints = 100;
    glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_QUAD_STRIP);
    for (float i = st; i <= numberofpoints / p + st; i += 1) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numberofpoints);
        float dx = r * cosf(theta);
        float dy = r * sinf(theta);
        float ddx = (r + (r * 0.25)) * cosf(theta);
        float ddy = (r + (r * 0.25)) * sinf(theta);
        glTexCoord2f(i * p / numberofpoints ,0); glVertex3d(dx + x, dy + y, 0 + z);
        glTexCoord2f(i * p / numberofpoints , 1); glVertex3d(ddx + x, ddy + y, 0 + z);
    }
    glEnd();
}
void drawBArc(float x, float y, float z, float r, float p, float st, int tex) {
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
void drawJamb(float x, float y, float z, float r,int tex,int number) {
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
            double POS[3] = { addx  + x  ,addy + y - (r * 22) - ((number == 1) ? 35 : 0) , addz + z -(r * 5.2)};
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
            float addx = ((faces[i][j] == 0 || faces[i][j] == 3 || faces[i][j] == 4 || faces[i][j] == 7) ? -(r/10) : (r/10)) + ((faces[i][j] == 1 || faces[i][j] == 2 || faces[i][j] == 5 || faces[i][j] == 6) ? r : -r);
            float addy = ((faces[i][j] == 1 || faces[i][j] == 0 || faces[i][j] == 4 || faces[i][j] == 5) ? r : -(r/2)) + ((faces[i][j] == 7 || faces[i][j] == 2 || faces[i][j] == 3 || faces[i][j] == 6) ? r : -r);
            float addz = ((faces[i][j] <= 3) ? -(r/20) : r/20) + ((faces[i][j] == 0 || faces[i][j] == 1 || faces[i][j] == 2 || faces[i][j] == 3) ? (r * 6) : (r * 4.5));
            double POS[3] = {  x + addx , y - (r * 21) + addy - ((number == 1) ? 35 : 0) , z + addz - (r * 5.2) };
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

void drawDomeoftheChain(float x, float y, float z) {
    // Number of vertices
    const int numVertices = 11;

    // Radius of the circle
    float radius = 150.0f;

    // Angle between each vertex
    float angleIncrement = 2.0f * M_PI / numVertices;

    // Array to hold the vertices
    GLfloat verticess[numVertices][3];

    // Calculate the position of each vertex
    for (int i = 0; i < numVertices; ++i)
    {
        float angle = i * angleIncrement;
        verticess[i][0] = radius * cos(angle) + x;
        verticess[i][1] = y;
        verticess[i][2] = radius * sin(angle) + z; // All vertices lie in the same plane in 3D
       
    }

    // Draw the polygon
    float length = 10;
    int tex = marble;
    glBindTexture(GL_TEXTURE_2D, marble2);
    glBegin(GL_QUADS);
    for (int i = 0; i < numVertices; ++i)
    {
        int second = 0;
        if (i + 1 < numVertices)second = i + 1;
        else second = 0;
        glTexCoord2f(0, 0); glVertex3f(verticess[i][0], verticess[i][1] - length, verticess[i][2]);
        glTexCoord2f(1, 0); glVertex3f(verticess[second][0], verticess[second][1] - length, verticess[second][2]);
        glTexCoord2f(1, 1); glVertex3fv(verticess[second]);
        glTexCoord2f(0, 1); glVertex3fv(verticess[i]);
    }
    glEnd();
    
    // draw the other one
    float yy = -60;
    glBindTexture(GL_TEXTURE_2D, marble2);
    glBegin(GL_QUADS);
    for (int i = 0; i < numVertices; ++i)
    {
        int second = 0;
        if (i + 1 < numVertices)second = i + 1;
        else second = 0;
        glTexCoord2f(0, 0); glVertex3f(verticess[i][0], verticess[i][1] - length + yy, verticess[i][2]);
        glTexCoord2f(1, 0); glVertex3f(verticess[second][0], verticess[second][1] - length + yy, verticess[second][2]);
        glTexCoord2f(1, 1); glVertex3f(verticess[second][0], verticess[second][1] + yy, verticess[second][2]);
        glTexCoord2f(0, 1); glVertex3f(verticess[i][0], verticess[i][1] + yy, verticess[i][2]);
    }
    glEnd();
    // draw ceil
    glBindTexture(GL_TEXTURE_2D, decor3);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < numVertices; ++i)
    {
        int second = 0;
        if (i + 1 < numVertices)second = i + 1;
        else second = 0;
        glTexCoord2f(0, 0); glVertex3fv(verticess[second]);
        glTexCoord2f(1, 0); glVertex3fv(verticess[i]);
        glTexCoord2f(0.5, 0.5); glVertex3f(x, y , z);
    }
    glEnd();
    // draw floor
    glBindTexture(GL_TEXTURE_2D, decor5);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < numVertices; ++i)
    {
        int second = 0;
        if (i + 1 < numVertices)second = i + 1;
        else second = 0;
        glTexCoord2f(0, 0); glVertex3f(verticess[second][0] , verticess[second][1] - 175 + yy, verticess[second][2]);
        glTexCoord2f(1, 0); glVertex3f(verticess[i][0], verticess[i][1] - 175 + yy, verticess[i][2]);
        glTexCoord2f(0.5, 0.5); glVertex3f(x, y - 175 + yy,  z);
    }
    glEnd();
    // draw the arch with the jambs 
    float numberofpoints = 100;
    float r = 5;
    length = 175;
    for (int ii = 0; ii < numVertices; ii++) {
        // jamb
        glBindTexture(GL_TEXTURE_2D, marble1);
        glBegin(GL_QUAD_STRIP);
        glLineWidth(3);
        for (int i = 0; i <= numberofpoints; i ++) {
            float theta = 2.0f * 3.1415926f * float(i) / float(numberofpoints);
            float dx = r * cosf(theta);
            float dy = r * sinf(theta);
            glTexCoord2f(i / numberofpoints, 0); glVertex3d(dx + verticess[ii][0], verticess[ii][1] + yy, verticess[ii][2] + dy);
            glTexCoord2f(i / numberofpoints, 1); glVertex3d(dx + verticess[ii][0], verticess[ii][1] - length + yy, verticess[ii][2] + dy);
        }
        glEnd();
        // arc
        int second = ((ii + 1 < numVertices) ? ii + 1 : 0);
        float centerX = (verticess[second][0] + verticess[ii][0]) / 2;
        float centerY = (verticess[second][1] + verticess[ii][1]) / 2;
        float centerZ = (verticess[second][2] + verticess[ii][2]) / 2;
        float m = (verticess[second][2] - verticess[ii][2]) / (verticess[second][0] - verticess[ii][0]);
        float b = verticess[second][2] - (m * verticess[second][0]);
        float radiussx = (verticess[second][0] - verticess[ii][0]) / 2;
        float radiuss = 30;
        glBindTexture(GL_TEXTURE_2D, decor2);
        glBegin(GL_QUAD_STRIP);
        for (int i = 0; i <= numberofpoints / 2; i++) {
            float theta = 2.0f * 3.1415926f * float(i) / float(numberofpoints);
            float now = i;
            float xarc = centerX + radiussx * cosf(theta);
            float yarc = centerY + radiuss * sinf(theta) + yy;
            float zarc = (m * xarc) + b;
            glTexCoord2d(float(i) * 4 / numberofpoints, 1 - (((centerY - 10) - yarc) / ((centerY - 10) - (verticess[ii][1] + yy)))); glVertex3f(xarc, yarc, zarc);
            glTexCoord2d(float(i) * 4 / numberofpoints, 1); glVertex3f(xarc, centerY - 10, zarc);

        }
        glEnd();
    }
    
    //the inner polygon 
    // Number of vertices
    const int numVertices1 = 6;

    // Radius of the circle
     radius = 75.0f;

    // Angle between each vertex
    float angleIncrement1 = 2.0f * M_PI / numVertices1;

    // Array to hold the vertices
    GLfloat verticess1[numVertices1][3];

    // Calculate the position of each vertex
    for (int i = 0; i < numVertices1; ++i)
    {
        float angle = i * angleIncrement1;
        verticess1[i][0] = radius * cos(angle) + x;
        verticess1[i][1] = y + 30;
        verticess1[i][2] = radius * sin(angle) + z;
    }
  
    // Draw the polygon
    length = 60;
    glBindTexture(GL_TEXTURE_2D, decor4);
    glBegin(GL_QUADS);
    for (int i = 0; i < numVertices1; ++i)
    {
        int second = 0;
        if (i + 1 < numVertices1)second = i + 1;
        else second = 0;
        glTexCoord2f(0, 0); glVertex3f(verticess1[i][0], verticess1[i][1] - length, verticess1[i][2]);
        glTexCoord2f(1, 0); glVertex3f(verticess1[second][0], verticess1[second][1] - length, verticess1[second][2]);
        glTexCoord2f(1, 1); glVertex3fv(verticess1[second]);
        glTexCoord2f(0, 1); glVertex3fv(verticess1[i]);
    }
    glEnd();
    // the dome 
    drawdome(x, y + 30, z, radius, dome4, dome4, 0);
    // the inner jambs
    length = 200;
    for (int ii = 0; ii < numVertices1; ii++) {
        // jamb
        glBindTexture(GL_TEXTURE_2D, marble2);
        glBegin(GL_QUAD_STRIP);
        glLineWidth(3);
        for (int i = 0; i <= numberofpoints; i++) {
            float theta = 2.0f * 3.1415926f * float(i) / float(numberofpoints);
            float dx = r * cosf(theta);
            float dy = r * sinf(theta);
            glTexCoord2f(i / numberofpoints, 0); glVertex3d(dx + verticess1[ii][0], verticess1[ii][1] + yy, verticess1[ii][2] + dy);
            glTexCoord2f(i / numberofpoints, 1); glVertex3d(dx + verticess1[ii][0], verticess1[ii][1] - length + yy, verticess1[ii][2] + dy);
        }
        glEnd();
    }
}
void drawtree(float x, float y, float z, float scale) {
    tree->pos.x = x;
    tree->pos.y = y;
    tree->pos.z = z;
    tree->scale = scale;
    tree->Draw();
}
void drawTreesInCup(float cupX, float cupY, float cupZ, float cupWidth, float cupHeight, float cupLength, int numTrees, int scale) {
    srand(42);

    for (int i = 0; i < numTrees; ++i) {
        // Generate pseudo-random coordinates within the cup
        float randomX = ((float)rand() / RAND_MAX) * cupWidth + cupX - cupWidth / 2.0;
        float randomY = ((float)rand() / RAND_MAX) * cupHeight + cupY;
        float randomZ = ((float)rand() / RAND_MAX) * cupLength + cupZ - cupLength / 2.0;

        // Set the tree size
        scale = scale + ((float)rand() / RAND_MAX) * 1.5;

        // Draw the tree at the generated coordinates
        drawtree(randomX, randomY, randomZ, scale);
    }
}
void drawgrass(float x, float y, float z, float lengthx, float lengthy, float lengthz) {
    int tex;
    for (int i = 0; i < 6; i++) {
        if (i == 4)tex = grass;
        else tex = demoAlshek;
        glBindTexture(GL_TEXTURE_2D, tex);
        glBegin(GL_QUADS);
        for (int j = 0; j < 4; j++) {
            float addx = ((faces[i][j] == 1 || faces[i][j] == 2 || faces[i][j] == 5 || faces[i][j] == 6) ? lengthx : -lengthx);
            float addy = ((faces[i][j] == 3 || faces[i][j] == 2 || faces[i][j] == 7 || faces[i][j] == 6) ? lengthy : -lengthy);
            float addz = ((faces[i][j] == 1 || faces[i][j] == 2 || faces[i][j] == 0 || faces[i][j] == 3) ? lengthz : -lengthz);
            double POS[3] = { x + addx, y + addy, z + addz };
            glTexCoord2f(TexCoor[j].x, TexCoor[j].y);
            glVertex3dv(POS);
        }

        glEnd();
    }

}
void drawCubee(float x, float y, float z, float length, float width, float height, int textureWall, int textureGround, int numTree, int scale) {


    float wallHeight = height / 14.0f;
    glEnable(GL_TEXTURE_2D);
    //drawgrass(x, y + (wallHeight- 0.2 * (wallHeight)), z, width, wallHeight, length);
    drawgrass(x, y + 0.1 * (wallHeight), z, width / 2 - (0.01 * (width / 2)), wallHeight / 13, length / 2 - (0.01 * (length / 2)));
    // Draw the front face
    glBindTexture(GL_TEXTURE_2D, textureWall);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x - width / 2, y, z + length / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width / 2, y, z + length / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width / 2, y + wallHeight, z + length / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x - width / 2, y + wallHeight, z + length / 2);
    glEnd();

    // Draw the back face
    glBindTexture(GL_TEXTURE_2D, textureWall);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x - width / 2, y, z - length / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width / 2, y, z - length / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width / 2, y + wallHeight, z - length / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x - width / 2, y + wallHeight, z - length / 2);
    glEnd();

    // Draw the left face
    glBindTexture(GL_TEXTURE_2D, textureWall);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x - width / 2, y, z + length / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x - width / 2, y, z - length / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x - width / 2, y + wallHeight, z - length / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x - width / 2, y + wallHeight, z + length / 2);
    glEnd();

    // Draw the right face
    glBindTexture(GL_TEXTURE_2D, textureWall);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width / 2, y, z + length / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width / 2, y, z - length / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width / 2, y + wallHeight, z - length / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width / 2, y + wallHeight, z + length / 2);
    glEnd();

    // Draw the bottom face
    glBindTexture(GL_TEXTURE_2D, textureWall);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x - width / 2, y, z + length / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width / 2, y, z + length / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width / 2, y, z - length / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x - width / 2, y, z - length / 2);
    glEnd();

    drawTreesInCup(x, y, z, width - (0.1 * width), 0, length - (0.1 * length), numTree, scale);
    glDisable(GL_TEXTURE_2D);

}
void drawHexagonalPrism(float x, float y, float z, float radius, float height, int textureSide1, int textureSide2, int textureTop) {

    const int sides = 6;
    const float angle = 2.0 * M_PI / sides;
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(280, 0.0f, 1.0f, 0.0f);
    glTranslatef(-x, -y, -z);
    // Draw the sides with textureSide1
    glBindTexture(GL_TEXTURE_2D, textureSide1);
    glBegin(GL_QUADS);
    for (int i = 0; i < sides - 1; ++i) {
        float x1 = x + radius * cos(angle * i);
        float z1 = z + radius * sin(angle * i);
        float x2 = x + radius * cos(angle * (i + 1));
        float z2 = z + radius * sin(angle * (i + 1));

        glTexCoord2f(0.0f, 0.0f); glVertex3f(x1, y, z1);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x1, y + height, z1);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x2, y + height, z2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x2, y, z2);
    }
    glEnd();

    // Draw the side with textureSide2
    glBindTexture(GL_TEXTURE_2D, textureSide2);
    glBegin(GL_QUADS);
    int i = sides - 1;
    float x1 = x + radius * cos(angle * i);
    float z1 = z + radius * sin(angle * i);
    float x2 = x + radius * cos(angle * 0);
    float z2 = z + radius * sin(angle * 0);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(x1, y, z1);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x1, y + height, z1);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x2, y + height, z2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x2, y, z2);
    glEnd();

    // Draw the top with textureTop
    glBindTexture(GL_TEXTURE_2D, textureTop);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < sides; ++i) {
        float x1 = x + radius * cos(angle * i);
        float z1 = z + radius * sin(angle * i);
        float x2 = x + radius * cos(angle * (i + 1));
        float z2 = z + radius * sin(angle * (i + 1));

        glTexCoord2f(0.5f, 0.5f); glVertex3f(x, y + height, z);
        glTexCoord2f(0.0f, 0.5f); glVertex3f(x1, y + height, z1);
        glTexCoord2f(1.0f, 0.5f); glVertex3f(x2, y + height, z2);
    }
    glEnd();
    glPopMatrix();
}
void demoNonKnown(float x, float y, float z, float radius, float height, int textureSide1, int textureSide2, int textureTop) {

    drawHexagonalPrism(x, y, z, radius, height, textureSide1, textureSide2, textureTop);
    float ri = radius + (0.1) * radius;
    float hi = height * (0.01);
    float yi = y + height;
    drawHexagonalPrism(x, yi, z, ri, hi, textureTop, textureTop, textureTop);
    float yh = yi + hi + 1.1 * (hi);
    float rh = radius - 0.1 * (radius);
    drawdome(x, yh, z, rh, demoAlshek, demoAlshek, 0);

}
void sound() {
    mciSendString("open \"bird22.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
    mciSendString("play mp3 repeat", NULL, 0, NULL);
}
void lastdraw(float x, float y, float z) {


}
void drawyossefagha(float x, float y, float z) {
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);

    drawdome(x + 10, y + 150, z + 17, 100, demoAlshek, demoAlshek, 0);
    for (int i = 0; i < 6; i++) {
        if (i == 2 || i == 3 || i == 0) {

            glBindTexture(GL_TEXTURE_2D, yossef);
        }


        else {
            glBindTexture(GL_TEXTURE_2D, demoAlshek);
        }


        glBegin(GL_QUADS);
        for (int j = 0; j < 4; j++) {
            float addx = 0;
            float addy = 0;
            float addz = 0;
            if (faces[i][j] <= 3)
            {   //right
                addz = 300;
            }
            if (faces[i][j] > 3) {
                //left
                addz = -300;
            }
            if (faces[i][j] == 2 || faces[i][j] == 5 || faces[i][j] == 6 || faces[i][j] == 1) {
                //front
                addx = 300;

            }
            if (faces[i][j] == 0 || faces[i][j] == 4 || faces[i][j] == 7 || faces[i][j] == 3) {
                //bacck
                addx = -300;

            }

            if (faces[i][j] == 0 || faces[i][j] == 4 || faces[i][j] == 1 || faces[i][j] == 5) {
                addy = -150;
            }
            if (faces[i][j] == 2 || faces[i][j] == 3 || faces[i][j] == 7 || faces[i][j] == 6) {
                addy = +150;
            }


            double POS[3] = { vertices[faces[i][j]][0] + x + addx ,vertices[faces[i][j]][1] + y + addy, vertices[faces[i][j]][2] + z + addz };
            glTexCoord2d(TexCoor[j].x, TexCoor[j].y);
            glVertex3dv(POS);
        }
        glEnd();
    }
}

void changeViewPort(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
    glLoadIdentity();									// Reset The Projection Matrix


    glEnable(GL_DEPTH_TEST);              // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                // The Type Of Depth Testing To Do
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glAlphaFunc(GL_GREATER, 0.1);
    glEnable(GL_ALPHA_TEST);
    glShadeModel(GL_SMOOTH);

    // Calculate The Aspect Ratio Of The Window
    gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 15000.0f);

    glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    // skybox
    SKYFRONT = LoadTexture("front.bmp", 255);
    SKYBACK = LoadTexture("back.bmp", 255);
    SKYLEFT = LoadTexture("left.bmp", 255);
    SKYRIGHT = LoadTexture("right.bmp", 255);
    SKYUP = LoadTexture("up.bmp", 255);
    SKYDOWN = LoadTexture("down.bmp", 255);
    ground2 = LoadTexture("stone4.bmp", 255);
    night = LoadTexture("night.bmp", 255);
    sun = LoadTexture("sun.bmp", 255);
    FLAG = LoadTexture("Flag_of_Palestine.bmp", 255);
    FLAG2 = LoadTexture("FLAG2.bmp", 255);
     domeMousa = LoadTexture("domeMousa.bmp", 255);
    domeMousaFace = LoadTexture("domeMousaFace.bmp", 255);
    domeMousaRoof = LoadTexture("domeMousaRoof.bmp", 255);
    domeMousaq = LoadTexture("domeMousaq.bmp", 255);
    domeMousaBottomDome = LoadTexture("domeMousaBottomDome.bmp", 255);
    dome = LoadTexture("dome.bmp", 255);
    dome1 = LoadTexture("dome1.bmp", 255);
    dome3 = LoadTexture("dome3.bmp", 255);
    dome4 = LoadTexture("dome4.bmp", 255);
    dome5 = LoadTexture("dome5.bmp", 255);
    carpet = LoadTexture("carpet.bmp", 255);
    H = LoadTexture("H.bmp", 255);
    stone = LoadTexture("stone.bmp", 255);
    stone1 = LoadTexture("stone2.bmp", 255);
    QaytBayfront = LoadTexture("QaytBayfront.bmp", 255);
    QaytBayside = LoadTexture("QaytBayside.bmp", 255);
    arc = LoadTexture("arc.bmp", 255);
    arc1 = LoadTexture("arc1.bmp", 255);
    arc2 = LoadTexture("arc2.bmp", 255);
    marble = LoadTexture("marble.bmp", 255);
    marble1 = LoadTexture("marble1.bmp", 255);
    marble2 = LoadTexture("marble2.bmp", 255);
    marble3 = LoadTexture("marble3.bmp", 255);
    decor1 = LoadTexture("decor1.bmp", 255);
    decor2 = LoadTexture("decor2.bmp", 255);
    decor3 = LoadTexture("decor3.bmp", 255);
    decor4 = LoadTexture("decor4.bmp", 255);
    decor5 = LoadTexture("decor5.bmp", 255);
    decor6 = LoadTexture("decor6.bmp", 255);
    decor7 = LoadTexture("decor7.bmp", 255);
    floor1 = LoadTexture("floor.bmp", 255);
    wood = LoadTexture("wood.bmp", 255);
    frontwall = LoadTexture("frontwall.bmp", 255);
    leftfrontwall = LoadTexture("leftfrontwall.bmp", 255);
    door = LoadTexture("door.bmp", 255);
    soor = LoadTexture("img.bmp", 255);
    wall = LoadTexture("wall.bmp", 255);
    grass = LoadTexture("grass.bmp", 255);
    grass2 = LoadTexture("grass2.bmp", 255);
    demoAlshekWall = LoadTexture("demoAlshekWall.bmp", 255);
    demoAlshekFace = LoadTexture("demoAlshekFace.bmp", 255);
    demoWall = LoadTexture("demoWall.bmp", 255);
    demoWallFace = LoadTexture("demoWallFace.bmp", 255);
    demoAlshek = LoadTexture("demoAlshek.bmp", 255);
    door2 = LoadTexture("greendoor.bmp", 255);  //green door
    wallout = LoadTexture("wallout.bmp", 255);
    roof = LoadTexture("roof.bmp", 255);


    //
   

    TEX = sun;
    //DomeOfRock Textures
    domeOfRockTex["arc"] = arc;
    domeOfRockTex["decor1"] = decor1;
    domeOfRockTex["decor7"] = decor7;
    domeOfRockTex["marble1"] = marble1;
    domeOfRockTex["arc1"] = arc1;
    domeOfRockTex["marble2"] = marble2;
    domeOfRockTex["wood"] = wood;
    domeOfRockTex["marble"] = marble;
    domeOfRockTex["leftfrontwall"] = leftfrontwall;
    domeOfRockTex["door"] = door;
    domeOfRockTex["frontwall"] = frontwall;
    domeOfRockTex["dome"] = dome;
    domeOfRockTex["dome5"] = dome5;
    domeOfRockTex["carpet"] = carpet;

    square.setTextures(domeOfRockTex);

    yossef = LoadTexture("yossef.bmp", 150);

    buildingTex["marble"] = marble;
    buildingTex["demoAlshek"] = demoAlshek;
    buildingTex["demoAlshekWall"] = demoAlshekWall;
    buildingTex["door2"] = door2;
    buildings.setTexture(buildingTex);

    // Character
    frontleg = LoadTexture("frontleg.bmp", 255);
    frontface = LoadTexture("frontface.bmp", 255);
    frontbody = LoadTexture("frontbody.bmp", 255);
    backface = LoadTexture("backface.bmp", 255);
    backbody = LoadTexture("backbody.bmp", 255);
    backleg = LoadTexture("backleg.bmp", 255);
    hand = LoadTexture("hand.bmp", 255);
    sideface = LoadTexture("sideface.bmp", 255);
    qmosque = new Qmosque();

   
    //Model
    tree = new Model_3DS();
    tree->Load("Tree1.3DS");
    Leaf.LoadBMP("bat.bmp");
    BARK.LoadBMP("bark_loo.bmp");
    tree->Materials[0].tex = BARK;
    tree->Materials[1].tex = Leaf;
    tree->Materials[2].tex = Leaf;
    tree->Materials[3].tex = Leaf;
    tree->Materials[4].tex = Leaf;
    tree->pos.x = -10;
    tree->pos.y = 0;
    tree->pos.z = 0;
    tree->scale = 1;



    domeDisplayList = glGenLists(1);
    glNewList(domeDisplayList, GL_COMPILE);
    
  
    ///////
    drawyossefagha(-2405.16, -100, 2000);



    // PlaySound(TEXT("tank-engine.wav"), NULL, SND_FILENAME | SND_ASYNC);
    square.drawSquare(0, -175, 400, 1000, demoAlshek, soor, stone1);

    demoNonKnown(600, -175, 300, 75, 150, demoWall, demoWallFace, wood);

    //  drawBuilding(-950, -175, -450, 300, 200, 250);
   //   drawQaytBay(-20, 0, 0, 0, -3.5 ,0);

    generalWall.outerWall(0, -260, 0, 11990, 90, 1000, wallout, roof);
   
    Draw_Skybox(0, -300, 0, 13000, 100, 11000, ground2, ground2, ground2, ground2, ground2, ground2);
    //left
    buildings.drawFirstHouse(140, -174, 1340);
    buildings.drawSecondHouse(310, -95, 1350);
    buildings.drawFirstHouse(488, -174, 1340);
    //right
    buildings.drawFirstHouse(-375, -174, 1340);
    buildings.drawSecondHouse(-545, -95, 1350);
    buildings.drawFirstHouse(-723, -174, 1340);
    //Qmosque
    glPushMatrix();
    glTranslatef(0, -246, 5000);
    glRotated(180, 0, 1, 0);
    glScalef(12, 12, 12);
    qmosque->qmosque();
    glPopMatrix();
    // tree->Draw();
    // drawsmthn(10, 0, 0, 5, 4);
 
    
    
    glEndList();
   
   
}
void drawsph(float a, float b, float c, float radius, int tex1) {
    glBindTexture(GL_TEXTURE_2D, tex1);
    for (int i = 0; i < slices; i++) {
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
            glTexCoord2f((float)j  / stacks, (float)i / slices);
            glVertex3f(x * zr0 * radius + a, y * zr0 * radius + c, z0 * radius);
            glTexCoord2f((float)j  / stacks, (float)(i + 1)/ slices);
            glVertex3f(x * zr1 * radius + a, y * zr1 * radius + c, z1 * radius);
        }
        glEnd();
    }
}
void drawBuilding(float x, float y, float z, float width, float height, float length, int tex1, int tex2, int tex3, int tex4, int tex5, int build) {
    float yh = y + height;
    float xh = x + 0.5 * (width);
    float zh = z + 0.5 * (length);
    float r = width / 4;
    //  1 الجدران الجانبية
    glBindTexture(GL_TEXTURE_2D, tex1);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, tex2);
    // 2الجدران الجانبية الأخرى
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
    glEnd();

    // الجدران الجانبية الأخرى 3
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, tex5);
    // 4 الجدران الجانبية الأخرى
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
    glEnd();

    // الأرضية
    glBindTexture(GL_TEXTURE_2D, tex4);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y, z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, tex4);
    // السقف
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
    glEnd();
    if (build == 1) {
        drawdome(xh, yh, zh, r, tex3, tex3, r);
    }


}
void drawDomeMousa(float x, float y, float z, float lengthx, float lengthy, float lengthz, int texFace, int texWall, int texroof, int texDome, int texFloore, int texRight) {
    float yi = y + lengthy + 0.2 * lengthy;
    float lengyd = 0.1 * lengthy;
    float lengzd = lengthz + (0.05 * (lengthz));
    float lengxf = lengthx + 0.2 * (lengthx);
    float lengzf = lengthz + 0.2 * (lengthz);
    drawBuilding(x, y, z, lengxf, 0.2 * lengthy, lengzf, texFloore, texFloore, texFloore, texFloore, texFloore, 2);
    drawBuilding(x + 0.1 * (lengthx), y + (0.2 * lengthy), z + 0.1 * (lengthz), lengthx, lengthy, lengthz, texWall, texWall, texFloore, texFloore, texRight, 2);
    drawBuilding(x + 0.1 * (lengthx), yi, z + 0.1 * (lengthz), lengthx, lengyd, lengthz, roof, roof, roof, roof, roof, 2);

    float yh = y + lengthy + 0.2 * lengthy + lengyd;
    float xh = x + 0.5 * (lengthx)+0.1 * (lengthz);
    float zh = z + 0.5 * (lengthz)+0.1 * (lengthz);
    float r = lengthx / 3;
    float ri = r + (0.2 * r);
    // drawHexagonalPrism(xh, yh, zh, r, r*0.5, wood, wood,  wood);
    drawdome(xh, yh, zh, r, texDome, domeMousaBottomDome, ri);
}

float kk = 0;
void render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutPostRedisplay();
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -2.0); 
    glScalef(0.05, 0.05, 0.05);
    sound();
    float currentFrame = static_cast<float>(glutGet(GLUT_ELAPSED_TIME));
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    Camera1();
  
    glCallList(domeDisplayList);
    if (camera.TPSz)
        drawCharacter();
   
    if (!nightt)
        Draw_Skybox(0, 0, 0, 13000, 13000, 13000, SKYFRONT, SKYBACK, SKYLEFT, SKYRIGHT, SKYUP, SKYDOWN);
    else
        Draw_Skybox(0, 0, 0, 13000, 13000, 13000, night, night, night, night, night, night);
    drawDomeoftheChain(600, 70, 1000);
    drawBuilding(-950, -175, -450, 300, 200, 250, demoAlshekFace, demoAlshekWall, demoAlshek, demoAlshek, demoAlshekWall, 1);
    drawDomeMousa(-2400, -240, -1500, 250, 200, 350, domeMousa, domeMousa, roof, domeMousaq, demoAlshek, domeMousaFace);
    
    /*if(onground){
    glBindTexture(GL_TEXTURE_2D, marble);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3d(-158.609, -160.096, 1142.84);
    glTexCoord2f(1, 0); glVertex3d(-156.609, -160.096, 1142.84);
    glTexCoord2f(1, 1); glVertex3d(-156.609, -160.096, 1169.84);
    glTexCoord2f(0, 1); glVertex3d(-158.609, -160.096, 1169.84);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, FLAG);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3d(-158.609, -160.096, 1169.84);
    glTexCoord2f(1, 0); glVertex3d(-140.609, -160.096, 1169.84);
    glTexCoord2f(1, 1); glVertex3d(-140.609, -160.096, 1185.84);
    glTexCoord2f(0, 1); glVertex3d(-158.609, -160.096, 1185.84);
    glEnd();
    }*/
    //x =  -160 , y = 100 , z = -0.01
    if(ondome){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, marble);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3d(-160, 80, 1000);
        glTexCoord2f(1, 0); glVertex3d(-162, 80, 1000);
        glTexCoord2f(1, 1); glVertex3d(-162, 127, 1000);
        glTexCoord2f(0, 1); glVertex3d(-160, 127, 1000);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, FLAG);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3d(-162, 127, 1000);
        glTexCoord2f(1, 0); glVertex3d(-130, 127, 1000);
        glTexCoord2f(1, 1); glVertex3d(-130, 143, 1000);
        glTexCoord2f(0, 1); glVertex3d(-162, 143, 1000);
        glEnd();
    glPopMatrix();
    }
    glPushMatrix();
    glTranslatef(0, 0, a);
    glRotatef(b, 0, 0, 1);
    glBindTexture(GL_TEXTURE_2D, marble);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3d(-160, 80, 1000);
    glTexCoord2f(1, 0); glVertex3d(-162, 80, 1000);
    glTexCoord2f(1, 1); glVertex3d(-162, 127, 1000);
    glTexCoord2f(0, 1); glVertex3d(-160, 127, 1000);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, FLAG);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3d(-162, 127, 1000);
    glTexCoord2f(1, 0); glVertex3d(-130, 127, 1000);
    glTexCoord2f(1, 1); glVertex3d(-130, 143, 1000);
    glTexCoord2f(0, 1); glVertex3d(-162, 143, 1000);
    glEnd();
    glPopMatrix();
 //   b->Draw();
    
    //////==============lighting================//
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_POSITION, LightPos);
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmb);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiff);
    glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpec);

    glEnable(GL_LIGHTING);
    glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, MatShn);
    glEnable(GL_COLOR_MATERIAL);
    glPushMatrix();
    float angel = 2.0 * 3.14 * kk;
    LightPos[2] = 6000 * sin(angel);
    LightPos[0] = 6000 * cos(angel);
    glTranslated(LightPos[0], LightPos[1] + 3500, LightPos[2]);
    glColor3f(1, 1, 1);
    drawsph(0, 0, 0, 1000, TEX);
    glTranslated(-LightPos[0], -LightPos[1] - 3500, -LightPos[2]);
    kk += 50;
    glPopMatrix();
    // ============================== //
    drawCubee(-510, -240, 1540, 140, 400, 450, demoAlshek, demoAlshek, 14, 10);
    drawCubee(450, -240, 1540, 140, 700, 450, demoAlshek, demoAlshek, 14, 10);
    drawCubee(1100.0f, -250.95, -140.00f, 700, 140, 600, demoAlshek, demoAlshek, 3, 50);
    drawCubee(-3500, -240, -4000, 2000, 3000, 600, demoAlshek, demoAlshek, 60, 15);
    drawCubee(3200, -240, -4000, 2000, 3000, 600, demoAlshek, demoAlshek, 40, 15);
    drawCubee(3500, -240, -1700, 2000, 3500, 600, demoAlshek, demoAlshek, 70, 15);
    drawCubee(3710.93, -240, 4197.05, 2000, 4000, 600, demoAlshek, demoAlshek, 80, 15);
    drawCubee(-3500, -240, 4000, 2000, 4000, 600, demoAlshek, demoAlshek, 90, 15);
    glEnable(GL_TEXTURE_2D);
    drawCube(197.665, -240, 2482.2, grass2);
    
   
    //glFlush();
    glutSwapBuffers();
}


int main(int argc, char* argv[]) {

    // Initialize GLUT
    glutInit(&argc, argv);
    // Set up some memory buffers for our display
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    // Set the window size
    glutInitWindowSize(1920, 1080);
    //glutPassiveMotionFunc(mouse_callback);
   /* PlaySound(TEXT("tank-engine.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);*/
   /* mciSendString("open \"sound1.mp4\" type mpegvideo alias mp4", NULL, 0, NULL);
    mciSendString("play mp4 repeat", NULL, 0, NULL);*/
   
    // Create the window with the title "Hello,GL"
    glutCreateWindow("Hello, GL");
    // Bind the two functions (above) to respond when necessary
    glutReshapeFunc(changeViewPort);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);
    glutPassiveMotionFunc(mouse_callback);
    glutDisplayFunc(render);
    const GLubyte* renderer = glGetString(GL_RENDERER);
    printf("Renderer: %s\n", renderer);
    // Very important!  This initializes the entry points in the OpenGL driver so we can 
    // call all the functions in the API.
    
    glutMainLoop();
    return 0;
}