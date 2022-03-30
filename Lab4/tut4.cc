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

GLdouble eye[] = { 0, 0, 10 };
GLdouble lookAt[] = { 0, 0, 0 };
GLdouble up[] = { 0, 1, 0 };


/**
 * We have two lights so we need two sets of lighting properties.
 *
 * NOTE: This would be better done with a struct or class that contains the
 * ambient, diffuse, specular, and position for each light. We've avoided that
 * here to keep this lab simple. Consider this for your assignments/project!
 */
GLfloat ambient[2][4] = {
    { 1, 1, 1, 1 },
    { 1, 1, 1, 1 }
};
GLfloat diffuse[2][4] = {
    { 1, 0, 0, 1 },
    { 0, 0, 1, 1 }
};
GLfloat specular[2][4] = {
    { 1, 1, 1, 1 },
    { 1, 1, 1, 1 }
};
GLfloat lightPos[2][4] = {
    { 5, -25, 5, 1 },
    { -5, 5, 5, 0 },
};

/**
 * The 0th material in each of these arrays is the default one. This is useful
 * for resetting the material after using a custom one.
 *
 * Find more materials here: http://devernay.free.fr/cours/opengl/materials.html
 */
GLfloat materialAmbient[2][4] = {
    { 0.2, 0.2, 0.2, 1.0 },
    { 0.0215, 0.1745, 0.0215, 1.0 }
};
GLfloat materialDiffuse[2][4] = {
    { 0.8, 0.8, 0.8, 1.0 },
    { 0.07568, 0.61424, 0.07568, 1.0 }
};
GLfloat materialSpecular[2][4] = {
    { 0, 0, 0, 1 },
    { 0.633, 0.727811, 0.633, 1.0 }
};
GLfloat materialShiny[2] = {
    0,
    0.6
};

GLfloat lightPosKeyboardStep = 0.5;

void setMaterials(unsigned int index) {
    /**
     * Call glMaterialfv three times to set GL_AMBIENT, GL_DIFFUSE, and GL_SPECULAR.
     * Call glMaterialf to set GL_SHININESS.
     *
     * Note: shininess is a float scalar and thus uses the f suffix, the other
     * properties are vectors and thus use the fv suffix.
     *
     * ADD CODE HERE!
     */
    // The first one is done for you, uncomment the line below.
    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient[index]);
}

void display(void) {
    for (unsigned int i = 0; i < 2; i++) {
        /**
         * We've stored the lighting properties in a 2D array.
         * There are two outer elements in the array, one for each light.
         * We can use `GL_LIGHT0 + i` to set the `i`th light.
         *
         * ADD CODE HERE!
         */
        // The first one is done for you, uncomment the line below.
        //glLightfv(GL_LIGHT0 + i, GL_POSITION, lightPos[i]);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(
        eye[0], eye[1], eye[2],
        lookAt[0], lookAt[1], lookAt[2],
        up[0], up[1], up[2]
    );

    glColor3f(0.5, 0.5, 0.5);
    glPushMatrix();
        glTranslatef(2, 0, 0);
        glRotatef(45, 0.25, -1, -0.25);
        setMaterials(0);
        // A bug in some GLUT libraries gives the wrong winding order for the
        // teapot vertices. This causes the vertex normals to be incorrect!
        // Without the right vertex normals our lighting will look rather
        // wrong. You do not need to worry about these glFrontFace calls for
        // other objects.
        glFrontFace(GL_CW);
        glutSolidTeapot(1);
        glFrontFace(GL_CCW);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-1.5, -0.5, -3);
        setMaterials(0);
        glutWireSphere(1, 20, 20);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.5, -1, -15);
        setMaterials(1);
        glutSolidSphere(1, 30, 30);
    glPopMatrix();

    glFlush();
}

void handleReshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 1, 100);

    glMatrixMode(GL_MODELVIEW);
}

void handleKeyboard(unsigned char key, int _x, int _y) {
    if (key == 'q') {
        exit(0);
    }

    if (key == 'a') {
        lightPos[1][0] -= lightPosKeyboardStep;
    } else if (key == 'd') {
        lightPos[1][0] += lightPosKeyboardStep;
    }

    display();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(300,300);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Tutorial 4");

    glutKeyboardFunc(handleKeyboard);
    glutReshapeFunc(handleReshape);
    glutDisplayFunc(display);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    /** Enable lighting calculations and two lights here!
     *
     * ADD CODE HERE
     */

    glutMainLoop();

    return 0;
}
