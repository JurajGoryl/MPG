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


     GLfloat lightPos[] = {100.0f, 100.0f, 100.0f, 1.0f};
     GLfloat lightColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
     GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glEnable(GL_LIGHT0);
    
    // Enable color tracking for materials
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
     
     glEnable(GL_TEXTURE_2D);

	if (!setTexture("textures/coble.bmp", &coble, true)) {
		std::cout << "Neotvoril sa" << std::endl;
		exit(1);
	}

     if(!setTexture("textures/coble-wall.bmp", &cobleWall, true)) {
          std::cout << "Neotvoril sa" << std::endl;
          exit(1);
     }


	glBindTexture(GL_TEXTURE_2D, coble);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glBindTexture(GL_TEXTURE_2D, cobleWall);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

     InitCollisionWalls();

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
