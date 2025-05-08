#include "../GL/glew.h"
#include "../include/display.h"
#include "../include/objects.h"
#include "../include/init.h"
#include "../include/input.h"
#include "../include/utils.h"
#include "../include/globals.h"
#include "../imageLoad.h"
#include <cmath>
#include <GL/glut.h>


void OnReshape(int w, int h)            
{
	glViewport(0, 0, w, h);             
	glMatrixMode(GL_PROJECTION);        
	glLoadIdentity();                  
	gluPerspective(fov, (double)w/h, nearPlane, farPlane); 
}

void OnInit(void)
{
    glFrontFace(GL_CW);					
    glPolygonMode(GL_FRONT, GL_FILL);   
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    

    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

  
    GLfloat globalAmbient[] = {0.05f, 0.05f, 0.05f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);


    
    GLfloat lampLightColor[] = {4.0f, 3.5f, 3.0f, 1.0f};
    
    for (int i = 1; i <= 4; i++) {
        glLightfv(GL_LIGHT0+i, GL_DIFFUSE, lampLightColor);
        glLightfv(GL_LIGHT0+i, GL_SPECULAR, lampLightColor);
        glLightf(GL_LIGHT0+i, GL_CONSTANT_ATTENUATION, 0.7f);
        glLightf(GL_LIGHT0+i, GL_LINEAR_ATTENUATION, 0.003f);
        glLightf(GL_LIGHT0+i, GL_QUADRATIC_ATTENUATION, 0.0002f);
        glLightf(GL_LIGHT0+i, GL_SPOT_CUTOFF, 180.0f);
    }

   
    if (!setTexture("textures/coble.bmp", &streetLamp.textureID, true) ||
        !setTexture("textures/coble.bmp", &coble, true) ||
        !setTexture("textures/coble-wall.bmp", &cobleWall, true)) {
        std::cerr << "Failed to load textures!" << std::endl;
        exit(1);
    }

    GenerateWoodTexture();


    InitCollisionWalls();
    LoadLampModel("models/lampa.obj");
    SetupLampBuffers();

    glutIdleFunc(OnIdle);

}

void InitCollisionWalls() {
    // Back wall (-Z)
      Walls[0] = {
        {0, 0, 1},      // Facing +Z (after 180° rotation)
        {0, -15, -100},  // Center point
        200,             // Width (X-axis size)
        50               // Height
    };
    
    // Front wall (+Z)
    Walls[1] = {
        {0, 0, -1},     // Facing -Z
        {0, -15, 100},  // Center point
        200,            // Width (X-axis size)
        50              // Height
    };
    
    // Right wall (+X)
    Walls[2] = {
        {-1, 0, 0},     // Facing -X (after 90° rotation)
        {100, -15, 0},  // Center point
        200,            // Width (Z-axis size)
        50              // Height
    };
    
    // Left wall (-X)
    Walls[3] = {
        {1, 0, 0},      // Facing +X (after -90° rotation)
        {-100, -15, 0}, // Center point
        200,            // Width (Z-axis size)
        50              // Height
    };
    
    playerRadius = 2.5f; // Player collision radius
}

