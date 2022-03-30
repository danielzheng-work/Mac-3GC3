#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
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

GLdouble eye[] = { 0, 0, 15 };
GLdouble lookAt[] = { 0, 0, 0 };
GLdouble up[] = { 0, 1, 0 };

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    /** Call gluLookAt here.
     */

    glColor3f(1, 1, 1);
    glutWireTeapot(1);

    glColor3f(0, 0, 1);
    glTranslatef(2, 2, -15);
    glutWireTeapot(1);

    glFlush();
}

void handleReshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /**
     * Call gluPerspective here.
     */

    glMatrixMode(GL_MODELVIEW);
}

void handleKeyboard(unsigned char key, int _x, int _y) {
    if (key == 'q') {
        exit(0);
    }

    if (key == '1') {
        /** Reset the gluLookAt vectors.
         */
        eye[0] = 0;
        eye[1] = 0;
        eye[2] = 15;
        lookAt[0] = 0;
        lookAt[1] = 0;
        lookAt[2] = 0;
        up[0] = 0;
        up[1] = 1;
        up[2] = 0;
        display();
    } else if (key == '2') {
        /** Change the look at vectors (eye, lookAt, up) such that
         *  you are looking directly at the blue teapot.
         */
        display();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(300,300);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Tutorial 3");

    glutKeyboardFunc(handleKeyboard);
    glutReshapeFunc(handleReshape);
    glutDisplayFunc(display);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glutMainLoop();

    return 0;
}
