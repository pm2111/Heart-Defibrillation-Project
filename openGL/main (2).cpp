#include<GL/glew.h>
#include<GL/freeglut.h>
#include<iostream>
#include<cstdlib>
using namespace std;


//To resize window, call this fcn
void changeViewport( int w, int h)
{
	glViewport(0,0,h,w);
}


//To render image, call this
void render()
{
	glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	//Initialise GLUT
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);    
	//Create window
	glutCreateWindow("Test");
	glutInitWindowSize(600, 600);   // Set the window's initial width & height
	glutInitWindowPosition(100, 100); // Position the window's initial top-left corner
	//glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(render); // Register display callback handler for window re-paint
	
	
	//THis allows us to call functions in the API
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "GLEW ERROR");
		return 1;
	}

	// Draw a Red 1x1 Square centered at origin
	
	glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    glVertex2f(-0.5f, -0.5f);    // x, y
    glVertex2f( 0.5f, -0.5f);
    glVertex2f( 0.5f,  0.5f);
    glVertex2f(-0.5f,  0.5f);
	glEnd();
	glFlush();
	glutMainLoop();
	Sleep(10000);
	


return 0;
}