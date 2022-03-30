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

/**
 * 1. No concept in this function is new. This draws an X/Y axis with tick
 *    marks every unit. Note that a call to gluOrtho2D is made in `main`.
 *    We're no longer working with a viewport that ranges from -1 to 1!
 */
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

/**
 * 2. You can ignore the details of this function. They are not
 *    relevant to this lab. These markers are helpful for understanding
 *    positioning.
 */
void drawAxisLabels() {
    // Draw a + on the positive XY corner of the viewport and a - on the
    // negative XY corner of the viewport.
    glColor3f(1, 1, 1);
    glRasterPos2f(9, 9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '+');
    glRasterPos2f(-9, -9);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '-');
}

void drawSquare() {
    glBegin(GL_TRIANGLES);
        glVertex2f(-1, 1);
        glVertex2f(1, 1);
        glVertex2f(-1, -1);

        glVertex2f(-1, -1);
        glVertex2f(1, 1);
        glVertex2f(1, -1);
    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    drawAxisLabels();
    drawXYAxes(10);
    glPopMatrix();

    glColor3f(0, 0, 1);
    // 3. Push a new matrix on to the stack: all transformations we make until a
    // new `glPushMatrix` call will be applied to the next vertices.
    glPushMatrix();
    // 4. Translate 2 units upwards, now we'll be rendering the square relative
    // to (0, 2). When we call `glPopMatrix` we'll lose this transformation and
    // any others we make!
    glTranslatef(0, 2, 0);
    drawSquare();
    // 5. Pop the matrix off the stack. Now all the transformations we made at
    // this place in the stack will no longer affect further vertices.

    glPopMatrix();

    glFlush();
}

void handleKeyboard(unsigned char key, int _x, int _y) {
    if (key == 'q') {
        exit(0);
    }
}

/* main function - program entry point */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitWindowSize(600,600);
    glutInitWindowPosition(300,300);
    glutCreateWindow("Tutorial 2");

    glutKeyboardFunc(handleKeyboard);
    glutDisplayFunc(display);
    gluOrtho2D(-10,10,-10,10);
    glutMainLoop();

    return 0;
}
