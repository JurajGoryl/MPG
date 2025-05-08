#include "../include/display.h"
#include "../include/objects.h"
#include "../include/init.h"
#include "../include/input.h"
#include "../include/utils.h"
#include "../include/globals.h"

#include <iostream>

#include <cmath>
#include <GL/glut.h>

void OnMouseButton(int button, int state, int x, int y)
{ 
    y = glutGet(GLUT_WINDOW_HEIGHT) - y;  

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        
        int bx = 10, by = 10, bw = 120, bh = 40;
        if (x >= bx && x <= bx + bw && y >= by && y <= by + bh) {
            flyingMode = !flyingMode;
            std::cout << (flyingMode ? "Flying mode ENABLED" : "Flying mode DISABLED") << std::endl;
            lastCommand = (flyingMode ? "Flying" : "Walking");
            glutPostRedisplay();
            return;
        }

        if (!flyingMode) {
            trany = 0.0f;
        }

        tocime = true;
        xx = x;
        yy = y;
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        tocime = false;
        xold = xnew;
        yold = ynew;
    }

    glutPostRedisplay();
}


void OnMouseMotion(int x, int y)
{ 
	y = glutGet(GLUT_WINDOW_HEIGHT) - y;

	if (tocime) {
		xnew = xold + (x - xx) / radius;
		ynew = yold + (y - yy) / radius;
		uhel = xnew * PIover180;
        lastCommand = "Pohyb misou";
		glutPostRedisplay();
	}
}

void OnSpecial(int key, int mx, int my) {
    float moveSpeed = 1.5f;
    float yaw = xnew;  
    float pitch = ynew; 
    
    float forwardX = -sin(yaw) * cos(pitch);
    float forwardY = flyingMode ? sin(pitch) : 0.0f;
    float forwardZ = -cos(yaw) * cos(pitch);
    
    float length = sqrt(forwardX*forwardX + forwardZ*forwardZ);
    forwardX /= length;
    forwardZ /= length;

    float newX = tranx;
    float newY = trany;
    float newZ = tranz;

    switch(key) {
        case GLUT_KEY_UP:
            lastCommand = "W";
            newX += forwardX * moveSpeed;
            newY -= forwardY * moveSpeed;
            newZ -= forwardZ * moveSpeed;
            break;
        case GLUT_KEY_DOWN:
            lastCommand = "S";
            newX -= forwardX * moveSpeed;
            newY += forwardY * moveSpeed;
            newZ += forwardZ * moveSpeed;
            break;
        case GLUT_KEY_LEFT: {
            lastCommand = "A";
            float strafeX = cos(yaw) * moveSpeed;
            float strafeZ = sin(yaw) * moveSpeed;
            newX += strafeX;
            newZ += strafeZ;
            break;
        }
        case GLUT_KEY_RIGHT: {
            lastCommand = "D";
            float strafeX = -cos(yaw) * moveSpeed;
            float strafeZ = -sin(yaw) * moveSpeed;
            newX += strafeX;
            newZ += strafeZ;
            break;
        } 
    }

    if (CanMoveTo(newX, trany, newZ)) {
        tranx = newX;
        trany = newY;
        tranz = newZ;
    }
    glutPostRedisplay();
}



void OnKeyboard(unsigned char key, int mx, int my) {
    float moveSpeed = 1.5f;
    float yaw = xnew;   
    float pitch = ynew; 
    
    float forwardX = -sin(yaw) * cos(pitch);
    float forwardY = flyingMode ? sin(pitch) : 0.0f;
    float forwardZ = -cos(yaw) * cos(pitch);
    
    float length = sqrt(forwardX*forwardX + forwardZ*forwardZ);
    forwardX /= length;
    forwardZ /= length;

    float newX = tranx;
    float newY = trany;
    float newZ = tranz;

    switch(key) {
        case 'w': case 'W':
            lastCommand = "W";
            newX += forwardX * moveSpeed;
            newY -= forwardY * moveSpeed;
            newZ -= forwardZ * moveSpeed;
            break;
        case 's': case 'S':
            lastCommand = "S";
            newX -= forwardX * moveSpeed;
            newY += forwardY * moveSpeed;
            newZ += forwardZ * moveSpeed;
            break;
        case 'a': case 'A': {
            lastCommand = "A";
            float strafeX = cos(yaw) * moveSpeed;
            float strafeZ = sin(yaw) * moveSpeed;
            newX += strafeX;
            newZ += strafeZ;
            break;
        }
        case 'd': case 'D': {
            lastCommand = "D";
            float strafeX = -cos(yaw) * moveSpeed;
            float strafeZ = -sin(yaw) * moveSpeed;
            newX += strafeX;
            newZ += strafeZ;
            break;
        }
        case 'o': case 'O': {
            float yaw = -xnew;
            float pitch = -ynew;
            
            float dirX = -sin(yaw) * cos(pitch);
            float dirY = sin(-pitch);
            float dirZ = -cos(yaw) * cos(pitch);
        
            float speed = 1.0f;
            thrownObject.x = -tranx;
            thrownObject.y = -trany;
            thrownObject.z = -tranz;
            thrownObject.vx = dirX * speed;
            thrownObject.vy = dirY * speed;
            thrownObject.vz = dirZ * speed;
            thrownObject.active = true;
            thrownObject.falling = false;
            lastCommand = "Throw";
            break;
        }
    }


    if (CanMoveTo(newX, trany, newZ)) {
        tranx = newX;
        trany = newY;
        tranz = newZ;
    }
    glutPostRedisplay();
}


void DrawButton() {
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    int buttonX = 10;
    int buttonY = 10;
    int buttonWidth = 120;
    int buttonHeight = 40;

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    
    glColor3f(0.1f, 0.5f, 0.8f); 
    glBegin(GL_QUADS);
    glVertex2i(buttonX, buttonY);
    glVertex2i(buttonX + buttonWidth, buttonY);
    glVertex2i(buttonX + buttonWidth, buttonY + buttonHeight);
    glVertex2i(buttonX, buttonY + buttonHeight);
    glEnd();


    glColor3f(1.0f, 1.0f, 1.0f);
    std::string label = flyingMode ? "Flying: ON" : "Flying: OFF";
    glRasterPos2i(buttonX + 10, buttonY + 15);
    for (char c : label) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}
