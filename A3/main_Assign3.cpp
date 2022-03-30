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
#include <iostream>

#include "particle3D.h"
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <vector>


int life = 0;

//angs of scence
int x_ang=0;
int y_ang=0;
int z_ang=0;

// windows Size
int s_width = 800;
int s_height = 600;


//check key function
bool animation =true;
bool light = false;
bool friction = false;
bool object = false;
bool hole = false;

//gravitational constant
float  gravity = 9.8/5;


//lights properties
GLfloat ambient[2][4] = {
    { 0.24, 0.32, 0.54, 1 },
    { 0.5, 0.45, 0.35, 1 }
};
GLfloat diffuse[2][4] = {
    { 0, 1, 0, 1 },
    { 0, 0, 1, 1 }
};
GLfloat specular[2][4] = {
    { 1, 1, 1, 1 },
    { 0.7, 0.5, 1, 1 }
};
GLfloat lightPos[2][4] = {
    { 60, 50, 60, 1 },
    { -60, 85, 60, 0.5 },
};

//material properties
GLfloat materialAmbient[4][4] = {
    { 0.24725, 0.1995, 0.0745, 1.0 },
    { 0.19225, 0.19225,0.19225, 1.0 },
    { 0.135, 0.2225, 0.1575, 1.0},
    { 0.2, 0.5, 0.2, 1.0}
};
GLfloat materialDiffuse[4][4] = {
    { 0.75164, 0.60648, 0.22648, 1.0 },
    { 0.50754, 0.50754, 0.50754, 1.0 },
    { 0.54, 0.89, 0.63, 1.0},
    { 0.01, 0.01, 0.01, 1.0}
};
GLfloat materialSpecular[4][4] = {
    { 0.628281, 0.555802, 0.366065, 1.0 },
    { 0.508273, 0.508273, 0.508273, 1.0 },
    { 0.316228, 0.316228, 0.316228, 1.0},
    { 0.4, 0.4, 0.4, 1.0}
};
GLfloat materialShiny[4] = {
    0.4,
    0.6,
    0.1,
    0.078125
};


std::vector<Particle3D> particleArray;

const char* instruction = "The following is the instruction for the key features: \n"
						  "key f : friction mode toggle \n"
						  "key r : reset particles \n"
						  "key l : turn on or off lights \n"
						  "key 1 : change location of light0 \n"
						  "key 2 : change location of light1 \n"
						  "key space bar : pause animation \n"
						  "key arrow up : rotate up scene about x-axis \n"
						  "key arrow down : rotate down scene about x-axis \n"
						  "key arrow left : rotate left scene about y-axis \n"
						  "key arrow right : rotate right scene about y-axis \n"
						  "key arrow page up :rotate CW scene about z-axis \n"
                          "key arrow page down:rotate CCW scene about z-axis \n"
						  "key q : exit the program \n"
                          "Additinal Featrue: \n"
                          "key o: object collision, particle gain momnetum after strick object\n"
                          "key h: create a square floor hole \n"
                          ;

//create new particle, and push into vector array
void newParticle(){
	Particle3D particle;
    particle.age += life;
	particleArray.push_back(particle);
}

//  initially create random number (10-39) of particle 
void createPaticles()
{	
	int count = rand() % 30 + 10;
	for (int i = 1; i <= count; i++) {
		newParticle();
	}
}

//set objects materials
void setMaterials(unsigned int index) {
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient[index]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse[index]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular[index]);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, materialShiny[index]);
}


//draw each particle in the array
void drawParticles(Particle3D p){
    glPushMatrix();
	    glColor3f(p.red, p.green, p.blue);
        glTranslatef(p.Position.mX, p.Position.mY, p.Position.mZ);
		glRotatef(p.rot_Angle[0], 1.0, 0.0, 0.0);
        glRotatef(p.rot_Angle[1], 0.0, 1.0, 0.0);
        glRotatef(p.rot_Angle[2], 0.0, 0.0, 1.0);
        setMaterials(p.material);
		glutSolidSphere((p.size), 20, 20);
    glPopMatrix();
}

//decreate the max height particle can reach every frame by gravity constant
void gravityForce(){
    for (int i = 0; i < particleArray.size(); i++){
		Particle3D* p = &particleArray[i];
        p->Direction.mY -=gravity;
        
    }
}

//check and update each particle status
void moveParticle()
{
	for (int i = 0; i < particleArray.size(); i++){
		Particle3D* p = &particleArray[i];
        if(object){
            Point3D objectLoc(15,0,15); //object location
            //check distance between object and particle
            if(objectLoc.distanceTo(p->Position)<= (9.9 + p->size)){
                p->speed = 3;//gain monmentum, AKA increase speed and max height
                p->Direction.mY =200;
                p->Position.mX += (p->Direction.mX*0.3);
                p->Position.mZ += (p->Direction.mZ*0.4);

            }
        }
        //check if particle is fall off floor
        if(abs(p->Position.mX)>50 || abs(p->Position.mZ)>50){
                p->speed =1.0;
                float sign_X = p->Position.mX / abs(p->Position.mX);
                float sign_Z = p->Position.mZ / abs(p->Position.mZ);
                //particle has size, which need to  be considered  too
                p->Direction.mX = sign_X *(p->size);
                p->Direction.mY -=50;
                p->Direction.mZ = sign_Z *(p->size);

        }
        else{
            //check if there is hole, and the distance between hole and particle, need to consider the size
            if( 10 +(p->Position.mX)<(-1*p->size) &&  10 - (p->Position.mZ)<(-1*p->size) &&hole){
                        p->speed =1.0;
                        p->Direction.mY =-50;
            }
            else{
            //particle movement within the floor
            if(p->speed >=0.035){
                if (p->Position.mY >= p->Direction.mY&& p->Direction.mY > 0.0) // tring to use the final direction location as limit..
                    {
                        p->Direction.mY *= -1;
                    }
                    //particle->Direction=  need to update new direction of the particle, new final point 
                if (p->Position.mY <= (p->size) && p->Direction.mY < 0.0)	{
                        p->Direction.mY *= -1;
                    if(friction) // check if friction exits
                        p->speed *= 0.4;
                    }
                }
            //when the speed is very small, particle will slide in the floor until die or fall off
            else if (p->Direction.mY < 0.0){
                p->Position.mY = (p->size);
                p->Position.mX += (p->Direction.mX*0.02);
                p->Position.mZ += (p->Direction.mZ*0.01);
            }
            }
            //consider the effect of scene ang to particle 
            p->Position.mX -= z_ang*0.05;
            p->Position.mZ += x_ang*0.05;

        }
        //update position
        p->Position = p->Direction.normalize().multiply(p->speed).movePoint(p->Position);
    }
}

//check if particle reach its lifespan
void checklife(){
    for(typeof(particleArray.begin()) item = particleArray.begin(); item != particleArray.end(); item++){
        if((*item).age <=life || (*item).Position.mY < -120){
           particleArray.erase(item); 
        }
        if(item == particleArray.end()){
            break;
        }
        
	}
}

//update particle rotation angle and draw  the particle
void simulation(){
	for(int i = 0; i < particleArray.size(); i++){
            particleArray[i].rot_Angle[0]++;
            particleArray[i].rot_Angle[1]++;
            particleArray[i].rot_Angle[2]++;

            drawParticles(particleArray[i]);
	}
    

}





void platform()
{
	// set floor
    glPushMatrix();
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_QUADS);
        glNormal3f(0.0, 1.0, 0.0);
        setMaterials(3);
    	glVertex3f(-50.0, 0.0, -50.0);
		glVertex3f(50.0, 0.0, -50.0);
		glVertex3f(50.0, 0.0, 50.0);
		glVertex3f(-50.0, 0.0, 50.0);
	    glEnd();
    glPopMatrix();
    //create hole 
    if(hole){
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_QUADS);
        setMaterials(0);
        glNormal3f(0.0, 1.0, 0.0);
    	glVertex3f(-20.0, 0.1, 10.0);
		glVertex3f(-10.0, 0.1, 10.0);
		glVertex3f(-10.0, 0.1, 20.0);
		glVertex3f(-20.0, 0.1, 20.0);
	    glEnd();
    glPopMatrix();
    }
	
}

void display(void)
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    //where to look at
	gluLookAt(0.0, 30.0, 100.0, 0.0, 0.0, 0.0, 0, 1, 0);
    // check if lights are on
    if(light){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    for (unsigned int i = 0; i < 2; i++) {
            glLightfv(GL_LIGHT0 + i, GL_POSITION, lightPos[i]);
            glLightfv(GL_LIGHT0 + i, GL_AMBIENT, ambient[i]);
            glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, diffuse[i]);
            glLightfv(GL_LIGHT0 + i, GL_SPECULAR, specular[i]);
            
    }
    }
    else{
        glDisable(GL_LIGHTING);
    }
    //rotate scene
    glRotatef(x_ang,1,0,0);
    glRotatef(y_ang,0,1,0);
    glRotatef(z_ang,0,0,1);

    //create object
    if(object){
        glPushMatrix();
	    glColor3f(0,0,0);
        glTranslatef(15,0,15);
        setMaterials(2);
		glutSolidSphere(10, 20, 20);
        glPopMatrix();
    }
    platform();
    simulation();
	glutSwapBuffers();
}


void FPS(int val)
{
    checklife();
    if(animation){
    life ++;
    gravityForce();
    newParticle();
	moveParticle();
	glutPostRedisplay();
    }
    glutTimerFunc(17, FPS, 0); 
}


void special(int key, int x, int y)
{
    switch (key){
    case GLUT_KEY_UP:
        x_ang--;
        break;
    case GLUT_KEY_DOWN:
        x_ang++;
        break;
    case GLUT_KEY_LEFT:
        y_ang--;
        break;
    case GLUT_KEY_RIGHT:
        y_ang++;
        break;
    case GLUT_KEY_PAGE_UP:
        z_ang--;
        break;
    case GLUT_KEY_PAGE_DOWN:
        z_ang++;
        break;
    }
}
void kbd(unsigned char key, int x, int y){ 
    switch(key){
        case 'f':
			friction = !friction;
			break;
		case 'r':
			particleArray.erase(particleArray.begin(),particleArray.end());
            //reset the life and particle array
            life = 0;
			createPaticles();
			break;
		case 'l':
            light = !light;
			break;
        case '1':
            if(!light)
                light=!light;
            else{
            //change location randomly
            lightPos[0][0] += (rand()%10 -5);
            lightPos[0][1] += (rand()%10);
            lightPos[0][2] += (rand()%10 -5);
            }
            break;
        case '2':
            if(!light)
                light= !light;
            else{
            lightPos[1][0] += (rand()%20 -10);
            lightPos[1][1] += (rand()%20);
            lightPos[1][2] += (rand()%20 -15);
            }
            break;
        case ' ':
            animation=!animation;
            break;
        case 'o':
            object=!object;
            break;
        case 'h':
            hole=!hole;
            break;
        case 'q':
			exit(0);
			break;

    }
	
}
// reshape the window
void reshape(int w, int h)
{
    s_width = w;        
    s_height = h;        
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective(100, 1, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void callBackInit(){
	createPaticles();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);	
	glutKeyboardFunc(kbd);
    glutSpecialFunc(special);
	glutTimerFunc(0, FPS, 0);
}

// main function - program entry point
int main(int argc, char** argv)
{
	srand(time(NULL));
    std::cout<<instruction<<std::endl;
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(s_width, s_height);
	glutInitWindowPosition(0,0);
    glutCreateWindow("Assignement 3");
    
    glEnable(GL_DEPTH_TEST);
    //backface culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);
    //set clear colour to white
    glClearColor(1.0, 1.0, 1.0, 0);
   
    
    //start the program!
	callBackInit();
	glutMainLoop();				//starts the event glutMainLoop
	return(0);					
}