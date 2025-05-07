#include "../include/display.h"
#include "../include/objects.h"
#include "../include/init.h"
#include "../include/input.h"
#include "../include/utils.h"
#include "../include/globals.h"

#include <cmath>
#include <GL/glut.h>

void OnMouseButton(int button, int state, int x, int y)
{ 
	y = glutGet(GLUT_WINDOW_HEIGHT) - y;

	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			tocime = true;
			xx = x;
			yy = y;
		}
		else {
			tocime = false;
			xold = xnew;
			yold = ynew;
		}
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
		glutPostRedisplay();
	}
}

void OnSpecial(int key, int mx, int my) {
    float moveSpeed = 4.0f;
    float yaw = xnew;  
    float pitch = ynew; 
    
    float forwardX = -sin(yaw) * cos(pitch);
    float forwardZ = -cos(yaw) * cos(pitch);
    
    float length = sqrt(forwardX*forwardX + forwardZ*forwardZ);
    forwardX /= length;
    forwardZ /= length;

    float newX = tranx;
    float newZ = tranz;

    switch(key) {
        case GLUT_KEY_UP:
            newX += forwardX * moveSpeed;
            newZ -= forwardZ * moveSpeed;
            break;
        case GLUT_KEY_DOWN:
            newX -= forwardX * moveSpeed;
            newZ += forwardZ * moveSpeed;
            break;
        case GLUT_KEY_LEFT: {
            float strafeX = cos(yaw) * moveSpeed;
            float strafeZ = sin(yaw) * moveSpeed;
            newX += strafeX;
            newZ += strafeZ;
            break;
        }
        case GLUT_KEY_RIGHT: {
            float strafeX = -cos(yaw) * moveSpeed;
            float strafeZ = -sin(yaw) * moveSpeed;
            newX += strafeX;
            newZ += strafeZ;
            break;
        }
    }

    if (CanMoveTo(newX, trany, newZ)) {
        tranx = newX;
        tranz = newZ;
    }
    glutPostRedisplay();
}

void OnKeyboard(unsigned char key, int mx, int my) {
    float moveSpeed = 4.0f;
    float yaw = xnew;   
    float pitch = ynew; 
    
    float forwardX = -sin(yaw) * cos(pitch);
    float forwardZ = -cos(yaw) * cos(pitch);
    
    float length = sqrt(forwardX*forwardX + forwardZ*forwardZ);
    forwardX /= length;
    forwardZ /= length;

    float newX = tranx;
    float newZ = tranz;

    switch(key) {
        case 'w': case 'W':
            newX += forwardX * moveSpeed;
            newZ -= forwardZ * moveSpeed;
            break;
        case 's': case 'S':
            newX -= forwardX * moveSpeed;
            newZ += forwardZ * moveSpeed;
            break;
        case 'a': case 'A': {
            float strafeX = cos(yaw) * moveSpeed;
            float strafeZ = sin(yaw) * moveSpeed;
            newX += strafeX;
            newZ += strafeZ;
            break;
        }
        case 'd': case 'D': {
            float strafeX = -cos(yaw) * moveSpeed;
            float strafeZ = -sin(yaw) * moveSpeed;
            newX += strafeX;
            newZ += strafeZ;
            break;
        }
    }

    if (CanMoveTo(newX, trany, newZ)) {
        tranx = newX;
        tranz = newZ;
    }
    glutPostRedisplay();
}
