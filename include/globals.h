#include <GL/glut.h>
#include <string>
#include <vector>

#pragma once

struct StreetLamp {
    GLuint VAO;                        // Vertex Array Object
    GLuint VBO[3];                     // Vertex Buffer Objects (0: vertices, 1: normals)
    GLuint textureID;
    std::vector<GLfloat> vertices;     // Vertex data
    std::vector<GLfloat> normals;      // Normal data
    std::vector<GLfloat> uvs;          // UV data (if applicable)
    GLfloat position[4];  // x,y,z,w (w=1 for point light)
    GLfloat lightColor[4]; // RGBA
    StreetLamp() : VAO(0), VBO{0, 0} {} // Constructor to initialize VAO and VBO
};

struct ThrownObject {
    float x, y, z;
    float vx, vy, vz;
    bool active;
    bool falling;
};

extern ThrownObject thrownObject;

struct Wall {
    float normal[3];  // Wall normal vector
    float point[3];   // A point on the wall
    float width;      // Wall width/depth
    float height;     // Wall height
};

extern StreetLamp streetLamp;

extern std::string lastCommand;

extern Wall Walls[4];
extern float playerRadius;    

extern GLuint coble;
extern GLuint lampTexture;
extern GLuint cobleWall; 

#define PI        3.141592653589793f
#define PIover180 0.017453292519943f

#define WOOD_TEX_SIZE 256

extern bool flyingMode;

extern GLuint woodTextureID;

extern bool animationRunning;
extern bool texturesEnabled;
extern float lightBrightness;
extern GLfloat lightColor[4];

extern const float GROUND_LEVEL;
extern const float MAX_HEIGHT;


extern float animateAngle;
extern float xnew, ynew;
extern float xold, yold;
extern float xx, yy;
extern bool tocime;
extern float uhel;
extern float tranz, tranx, trany; 
extern float radius;

extern float fov;
extern float nearPlane;
extern float farPlane;
