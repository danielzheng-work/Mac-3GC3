#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
#include <stdio.h>
#include <stdlib.h>

float y = 0.0;

void drawXYAxes(int size) {
    glBegin(GL_LINES);
        glColor3f(1, 0, 0);
        glVertex2f(-size, 0);
        glVertex2f(size, 0);
        for (int i = -size; i <= size; i++) {
            glVertex2f(i, 0.5);
            glVertex2f(i, -0.5);
        }

        glColor3f(0, 1, 0);
        glVertex2f(0, -size);
        glVertex2f(0, size);
        for (int i = -size; i <= size; i++) {
            glVertex2f(0.5,i);
            glVertex2f(-0.5,i);
        }
    glEnd();
}

void drawAxisLabels() {
    glColor3f(1, 1, 1);
    glRasterPos2f(9, 9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '+');
    glRasterPos2f(-9, -9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '-');
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);


   
    glPushMatrix();
    drawAxisLabels();
    drawXYAxes(10);
    glPopMatrix();

    glColor3f(0, 0, 1);




    /**
     * NOTE: Your code should *only* go below here.
     * There is no need to edit elsewhere.
     */



 glPushMatrix();
        glTranslatef(0, 5, 0);
        glScalef(1+y, 1+y, 1);
        glutSolidTeapot(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-5, 0, 0);
        glPushMatrix();
            glScalef(1, 1+y, 1);
            glutSolidTeapot(1.0);
        glPopMatrix();
        glTranslatef(0, -5, 0);
        glutSolidTeapot(1.0);
    glPopMatrix();
    /**
     * NOTE: Your code should *only* go above here.
     */

    glFlush();
}

void handleKeyboard(unsigned char key, int _x, int _y) {
    if (key == 'q') {
        exit(0);
    }

    if (key == ' ') {
        y += 0.1;
        display();
    }
}

/* main function - program entry point */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitWindowSize(600,600);
    glutInitWindowPosition(300,300);
    glutCreateWindow("Tutorial 2 Graded");

    glutKeyboardFunc(handleKeyboard);
    glutDisplayFunc(display);
    gluOrtho2D(-10,10,-10,10);
    glutMainLoop();

    return 0;
}
