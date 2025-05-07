#include "../include/display.h"
#include "../include/objects.h"
#include "../include/init.h"
#include "../include/input.h"
#include "../include/utils.h"
#include "../include/globals.h"

#include <cmath>
#include <GL/glut.h>

void OnDisplay(void)				   
{
    glClearColor(0.8, 0.8, 0.8, 0.0);  
    glClearDepth(1.0f);

    glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);      
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);   

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glRotatef(-180 * ynew / PI, 1.0f, 0.0f, 0.0f);	
	glRotatef(180 * xnew / PI, 0.0f, 1.0f, 0.0f);	
	glTranslatef(tranx, trany, tranz);				

	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(50, 0, 0);
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 50, 0);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 50);
	glEnd();
	glEnable(GL_LIGHTING);

	DrawPlane(100);
     DrawAllWalls();
     DrawWallCollisionBounds();

    glFlush();		
    glutSwapBuffers(); 
}

