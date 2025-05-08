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
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-180 * ynew / PI, 1.0f, 0.0f, 0.0f);
    glRotatef(180 * xnew / PI, 0.0f, 1.0f, 0.0f);
    glTranslatef(tranx, trany, tranz);


    DrawLamps();

    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3f(1, 0, 0); glVertex3f(0,0,0); glVertex3f(50,0,0); // X
    glColor3f(0, 1, 0); glVertex3f(0,0,0); glVertex3f(0,50,0); // Y
    glColor3f(0, 0, 1); glVertex3f(0,0,0); glVertex3f(0,0,50); // Z
    glEnd();
    glEnable(GL_LIGHTING);

    DrawPlane(100);
    DrawAllWalls();
    DrawWallCollisionBounds();
    DrawBox();


    if (thrownObject.active) {
        glPushMatrix();
        glTranslatef(thrownObject.x, thrownObject.y, thrownObject.z);
        glColor3f(1, 1, 0);
        glutSolidSphere(1.0, 20, 20);
        glPopMatrix();
    }
 

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);

    DrawWindowObject();


    DrawButton();
    DrawUIMessage();
    glutSwapBuffers();

}

