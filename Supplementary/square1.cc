#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>

/* display function - GLUT display callback function
 *		clears the screen, draws a square, and displays it
 */
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POLYGON);
		glVertex2f(-0.5, -0.5);
		glVertex2f(-0.5, 0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(0.5, -0.5);
	glEnd();


	glFlush();
}

/* main function - program entry point */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT

	glutCreateWindow("square");	//creates the window
	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutMainLoop();				//starts the event loop

	return(0);					//return may not be necessary on all compilers
}
