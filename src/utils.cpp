#include "../include/globals.h"
#include "../include/utils.h"
#include "../include/globals.h"

#include <cmath>
#include <GL/glut.h>

bool CanMoveTo(float x, float y, float z) {
    for (int i = 0; i < 4; i++) {
        Wall wall = Walls[i];
        
        // Calculate distance from wall
        float wallDist = 
            (x - wall.point[0]) * wall.normal[0] +
            (y - wall.point[1]) * wall.normal[1] + 
            (z - wall.point[2]) * wall.normal[2];
        
        // Check if within wall bounds
        bool withinWidth = false;
        bool withinHeight = (y >= wall.point[1] - playerRadius) && 
                           (y <= wall.point[1] + wall.height + playerRadius);
        
        if (i == 0 || i == 1) { // Front/back walls
            withinWidth = (x >= wall.point[0] - wall.width/2 - playerRadius) && 
                          (x <= wall.point[0] + wall.width/2 + playerRadius);
        } else { // Left/right walls
            withinWidth = (z >= wall.point[2] - wall.width/2 - playerRadius) && 
                          (z <= wall.point[2] + wall.width/2 + playerRadius);
        }
        
        if (abs(wallDist) < playerRadius && withinWidth && withinHeight) {
            return false;
        }
    }
    return true;
}


