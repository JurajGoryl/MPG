#include "../include/globals.h"
#include "../include/utils.h"
#include "../include/globals.h"

#include <cmath>
#include <GL/glut.h>

bool CanMoveTo(float x, float y, float z) {
    // Height limits first
    if (y < GROUND_LEVEL || y > MAX_HEIGHT) {
        return false;
    }

    for (int i = 0; i < 4; i++) {
        Wall wall = Walls[i];
        
        // Calculate distance from wall plane
        float wallDist = 
            (x - wall.point[0]) * wall.normal[0] +
            (y - wall.point[1]) * wall.normal[1] + 
            (z - wall.point[2]) * wall.normal[2];
        
        // Check if within wall bounds
        bool withinBounds = false;
        if (i == 0 || i == 1) { // Front/back walls
            withinBounds = 
                (x >= wall.point[0] - wall.width/2 - playerRadius) &&
                (x <= wall.point[0] + wall.width/2 + playerRadius) &&
                (y >= wall.point[1] - playerRadius) &&
                (y <= wall.point[1] + wall.height + playerRadius);
        } else { // Left/right walls
            withinBounds = 
                (z >= wall.point[2] - wall.width/2 - playerRadius) &&
                (z <= wall.point[2] + wall.width/2 + playerRadius) &&
                (y >= wall.point[1] - playerRadius) &&
                (y <= wall.point[1] + wall.height + playerRadius);
        }
        
        if (fabs(wallDist) < playerRadius && withinBounds) {
            return false;
        }
    }
    return true;
}

void menuHandler(int option) {
    switch (option) {
        case 1: 
            lastCommand = "Reset";
            tranx = 0.0f;
            trany = 0.0f;
            tranz = -10.0f;
            uhel = 0.0f;
            xx = yy = xold = yold = xnew = ynew = 0.0f;
            glutPostRedisplay();
            break;
        case 2:
        lastCommand =  (!animationRunning ? "Animation start" :"Animation stop");
            animationRunning = !animationRunning;
            break;
        case 3: 
            texturesEnabled = !texturesEnabled;
            lastCommand = (texturesEnabled ? "Textures enabled" : "Textures disabled");
            glutPostRedisplay();
            break;
        case 4: 
            lastCommand = (lightBrightness < 0.8f) ? "Lights UP" : "Lights Down";
            lightBrightness = (lightBrightness < 0.8f) ? 0.85f : 0.4f;
            glutPostRedisplay();
            break;
        case 5: 
            exit(0);
            break;
    }
}

void DrawUIMessage() {
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 0.0f);  // Yellow text

    std::string label = "Last command: " + lastCommand;

    glRasterPos2i(10, windowHeight - 30);  // Top-left
    for (char c : label) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glEnable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}