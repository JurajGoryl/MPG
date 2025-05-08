// Autor : Juraj Goryl || ID = 240913
// [X] Animace (1b)
// [X] Osvětlení (1b)
// [X] Volný pohyb v horizontální rovině (1b) 
// [X] Menu (2 b)
// [X] Výpis textu (2b)
// [X] Blender model (1b) 
// [X] Lietanie (2b)
// [X] Hod předmětu (2b)
// [X] Tlačítka (2b) 
// [X] Průhlednost (1b) 
// [X] Neprůchozí objekt (2b) - kazda stena je nepruchozi ze vsech stran
// [X] Texturování (2b)


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
