#include "../include/display.h"
#include "../include/objects.h"
#include "../include/init.h"
#include "../include/input.h"
#include "../include/utils.h"
#include "../include/globals.h"

#include <cmath>
#include <GL/glut.h>



void DrawPlane(int size)
{
	glPushMatrix();
	glTranslatef(0, -15, 0);

	GLboolean isLightingEnabled;
	glGetBooleanv(GL_LIGHTING, &isLightingEnabled);
	if (isLightingEnabled) {
		glDisable(GL_LIGHTING);
	}

     glColor3f(0.5,0.5,0.5);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, coble);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3i(-size, 0, size);
	glTexCoord2f(0.0f, 1.0f); glVertex3i(-size, 0, -size);
	glTexCoord2f(1.0f, 1.0f); glVertex3i(size , 0, -size);
	glTexCoord2f(1.0f, 0.0f); glVertex3i(size , 0, size);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	if (isLightingEnabled) {
		glEnable(GL_LIGHTING);
	}

	glPopMatrix();
}


GLfloat wallVertices[] = {
    0.0f, 0.0f, 0.0f,
    200.0f, 0.0f, 0.0f,
    200.0f, 50.0f, 0.0f,
    0.0f, 50.0f, 0.0f
};


void DrawWall()
{

GLfloat wallColor[] = {0.8f, 0.8f, 0.8f, 1.0f}; // Brighter color
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wallColor);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, cobleWall);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord2f(4.0f, 0.0f); glVertex3f(200.0f, 0.0f, 0.0f);
    glTexCoord2f(4.0f, 2.0f); glVertex3f(200.0f, 50.0f, 0.0f);
    glTexCoord2f(0.0f, 2.0f); glVertex3f(0.0f, 50.0f, 0.0f);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

void DrawAllWalls()
{
     glPushMatrix();
     glTranslatef(100.0f, 0.0f, -100.0f); // bottom-left corner
     glRotatef(180.0f, 0.0f, 1.0f, 0.0f); // Rotate to face inward
     glTranslatef(0, -15, 0);
     DrawWall();
     glPopMatrix();

    // Front wall (along +Z)
    glPushMatrix();
    glTranslatef(-100.0f, 0.0f, 100.0f); // top-left corner
   glTranslatef(0, -15, 0);
    DrawWall();
    glPopMatrix();

      // Right wall (along +X)
    glPushMatrix();
    glTranslatef(100.0f, 0.0f, 100.0f); // bottom-right corner
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f); // Rotate to face inward
   glTranslatef(0,-15,0);
    DrawWall();
    glPopMatrix();

    // Left wall (along -X)
    glPushMatrix();
    glTranslatef(-100.0f, 0.0f, -100.0f); // bottom-left corner
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f); // Rotate to face inward
   glTranslatef(0,-15,0);
    DrawWall();
    glPopMatrix();
}

void DrawWallCollisionBounds() {
   glDisable(GL_LIGHTING);
    glColor3f(1, 0, 0);
    glLineWidth(2.0f);
    
    for (int i = 0; i < 4; i++) {
        Wall wall = Walls[i];
        glBegin(GL_LINE_LOOP);
        
        if (i == 0 || i == 1) { // Front/back walls
            float z = wall.point[2];
            glVertex3f(wall.point[0] - wall.width/2, wall.point[1], z);
            glVertex3f(wall.point[0] + wall.width/2, wall.point[1], z);
            glVertex3f(wall.point[0] + wall.width/2, wall.point[1] + wall.height, z);
            glVertex3f(wall.point[0] - wall.width/2, wall.point[1] + wall.height, z);
        } else { // Left/right walls
            float x = wall.point[0];
            glVertex3f(x, wall.point[1], wall.point[2] - wall.width/2);
            glVertex3f(x, wall.point[1], wall.point[2] + wall.width/2);
            glVertex3f(x, wall.point[1] + wall.height, wall.point[2] + wall.width/2);
            glVertex3f(x, wall.point[1] + wall.height, wall.point[2] - wall.width/2);
        }
        
        glEnd();
    }
    
    glEnable(GL_LIGHTING);
}

