#include "../include/globals.h"
#include <string>
#include <GL/glut.h>

GLuint coble;
GLuint cobleWall;
GLuint lampTexture;

StreetLamp streetLamp;

Wall Walls[4];
float playerRadius;

#define PI        3.141592653589793f
#define PIover180 0.017453292519943f

#define WOOD_TEX_SIZE 256

GLuint woodTextureID;


float animateAngle;
float xnew = 0, ynew = 0;
float xold = 0, yold = 0;
float xx = 0, yy = 0;
bool tocime = false;
float uhel = 0;
float tranz = 0, tranx = 0, trany = 0; 
float radius = 150;

float fov = 60.0;
float nearPlane = 0.1;
float farPlane = 150.0;
