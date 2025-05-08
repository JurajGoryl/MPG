#include <GL/glew.h>
#include "./include/display.h"
#include "./include/objects.h"
#include "./include/init.h"
#include "./include/input.h"
#include "./include/utils.h"
#include "./include/globals.h"
#include <cmath>
#include <GL/glut.h>


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);					
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); 
	glutInitWindowSize(640, 480);			
    glutInitWindowPosition(200, 200);		
    
	glutCreateWindow("Projekt 2025|Autor: Juraj Goryl");	
  
    glewInit();
    glutDisplayFunc(OnDisplay);				
    glutReshapeFunc(OnReshape);				
    glutMouseFunc(OnMouseButton);			
    glutMotionFunc(OnMouseMotion);			
    glutSpecialFunc(OnSpecial);
    glutKeyboardFunc(OnKeyboard);
	OnInit();

    glutCreateMenu(menuHandler);
    glutAddMenuEntry("Reset Camera Position", 1);
    glutAddMenuEntry("Toggle Animation", 2);
    glutAddMenuEntry("Toggle Textures", 3);
    glutAddMenuEntry("Toggle Light Brightness", 4);
    glutAddMenuEntry("Exit", 5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	glutMainLoop();

    return 0;
}
