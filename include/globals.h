#pragma once
#include <GL/glut.h>

struct Wall {
    float normal[3];  // Wall normal vector
    float point[3];   // A point on the wall
    float width;      // Wall width/depth
    float height;     // Wall height
};
extern Wall Walls[4];
extern float playerRadius;    

extern GLuint coble;
extern GLuint cobleWall; 

#define PI        3.141592653589793f
#define PIover180 0.017453292519943f

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
