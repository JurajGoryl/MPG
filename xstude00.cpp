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
    
	glutCreateWindow("Projekt 2023 – Autor: xstude00");	

     glutDisplayFunc(OnDisplay);				
     glutReshapeFunc(OnReshape);				
     glutMouseFunc(OnMouseButton);			
     glutMotionFunc(OnMouseMotion);			
     glutSpecialFunc(OnSpecial);
     glutKeyboardFunc(OnKeyboard);


	OnInit();
	
	glutMainLoop();

    return 0;
}
