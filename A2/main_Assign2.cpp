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

#include "particle2D.h"
#include <cstdlib>
#include <ctime>
#include <vector>

// windows Size
int s_width = 800;
int s_height = 600;
//check if the buttons press
bool checkLMB = false;
bool checkRMB = false;
//check if animation is run
bool pause = false;	
//check if need to hidden particle on window
bool hidden = false;
Point2D mousePoint;

std::vector<Particle2D> particleArray;

const char* instruction = "The following is the instruction for the key features: \n"
						  "key a : add new particle \n"
						  "key d : delete particle \n"
						  "key w : increase the range \n"
						  "key s : decrease the range \n"
						  "key i : increase the speed \n"
						  "key k : decrease the speed \n"
						  "key p : stop if the animation is running, start if it is stopped \n"
						  "key r : reset the particles \n"
						  "key h : all the particles disappeared, hit again will appear again at same location \n"
						  "key c : randomly change the color of the particles \n"
						  "key b : randomly increase the size of particle that cursor is within their rang \n"
						  "key q : exit the program \n";

//create random number of particles between 50-330,  and add them into array

void createPaticles()
{	
	int count = rand() % 281 + 50;
	for (int i = 1; i <= count; i++) {
		Particle2D point;
		point.Position.mX= (point.Position.mX * s_width);
		point.Position.mY= (point.Position.mY * s_height);
		particleArray.push_back(point);
		
	}
}

//draw and display each particle in the array
void drawParticles(void){
	if(!hidden){
	for(int i = 0; i < particleArray.size();i++){
		glPointSize(particleArray[i].size);
		glBegin(GL_POINTS);
			glColor3f(particleArray[i].red, particleArray[i].green, particleArray[i].blue);
			glVertex2f(particleArray[i].Position.mX,particleArray[i].Position.mY);
		glEnd();
	}
	}
	
}

// update the partice status when any mouse buttons pressed, if any properties of the particle changes
void pStateUpdate()
{   
		if(checkLMB)
		{
			for(int i = 0; i < particleArray.size();i++){
				Particle2D p = particleArray[i];	
			//check if cursor location is within the range of particle
				if(particleArray[i].Position.distanceTo(mousePoint)<= particleArray[i].range){
				p.Direction = p.Direction.createVector(mousePoint, p.Position).normalize(); //getting direction vector, and change its length to unit length
				p.Position = p.Direction.multiply(p.speed).movePoint(p.Position); 			// update the new position of the particle
				particleArray[i]=p;
			}
			}
		}
		if(checkRMB)
		{
			for(int i = 0; i < particleArray.size();i++){
				Particle2D p = particleArray[i];	
				if(particleArray[i].Position.distanceTo(mousePoint)<= particleArray[i].range){

				p.Direction = p.Direction.createVector(p.Position, mousePoint).normalize();
				p.Position = p.Direction.multiply(p.speed).movePoint(p.Position);
				particleArray[i]=p;
			}
			}
		}
	
}


void display(void)
{	
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, s_width, 0, s_height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	drawParticles();
	glutSwapBuffers();
}

//mouse bottom function
void mouse(int btn, int state, int x, int y){
    
    if (btn == GLUT_LEFT_BUTTON){
        
        if (state == GLUT_UP){
			checkLMB = false;
        }
        
        if (state == GLUT_DOWN){
			checkLMB = true;
			Point2D p(x, s_height-y);  			
			mousePoint = p; 				// update mouse location
        }
    }

	if (btn == GLUT_RIGHT_BUTTON){
        
        if (state == GLUT_UP){
			checkRMB = false;
        }
        
        if (state == GLUT_DOWN){
			checkRMB = true;
			Point2D p(x, s_height-y);  
			mousePoint = p; 				
        }
    }
}

//mouse motion function 
void motion (int x, int y){

    Point2D p(x, s_height-y); 
	mousePoint = p;
}

void passive (int x, int y){
    Point2D p(x, s_height-y); 
	mousePoint = p; 
}

void FPS(int val)
{
	//check if the animation is in running mode
   if(!pause){
	pStateUpdate();
	glutPostRedisplay();
   }
    glutTimerFunc(17, FPS, 0); 
}

void kbd(unsigned char key, int x, int y){
	Particle2D addOn;
	int index;  //the index of the closest particle to cursor in array 
	int miniDis=(particleArray[0].Position.distanceTo(mousePoint)); // the smallest distance between particle and cursor 
    switch(key){
        case 'a':
			addOn.Position=mousePoint;
			particleArray.push_back(addOn);
			break;
		case 'd':
			for(int i=0;i<particleArray.size();i++){
				if(particleArray[i].Position.distanceTo(mousePoint)<=miniDis){
						miniDis= particleArray[i].Position.distanceTo(mousePoint);
						index =i;
				}
			}
			particleArray.erase(particleArray.begin()+(index));
			break;
		case 'w':
			for(int i=0;i<particleArray.size();i++){
				particleArray[i].range+=5;
				}
			break;
		case 's':
			for(int i=0;i<particleArray.size();i++){
				particleArray[i].range-=5;
			}
			break;
		case 'i':
			for(int i=0;i<particleArray.size();i++){
				particleArray[i].speed+=2;
				}
			break;
		case 'k':
			for(int i=0;i<particleArray.size();i++){
				if(particleArray[i].speed>0){
				particleArray[i].speed-=1;
				}
			}
			break;
		case 'p':
			pause=!pause;
			break;
		case 'r':
			particleArray.erase(particleArray.begin(),particleArray.end());
			createPaticles();
			break;
		case 'h':
			hidden = !hidden;
			break;
		case 'c':
			for(int i=0;i<particleArray.size();i++){
				particleArray[i].red+=(0.5-static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
				particleArray[i].green+=(0.5-static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
				particleArray[i].blue+=(0.5-static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
			}
			break;
		case 'b':
			for(int i = 0; i < particleArray.size();i++){
				Particle2D p = particleArray[i];	
				if(particleArray[i].Position.distanceTo(mousePoint)<= particleArray[i].range){
		
				particleArray[i].size+=rand()%5;
			}
			}
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
	

}

void callBackInit(){
	glutDisplayFunc(display);	
	glutKeyboardFunc(kbd);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
    glutMotionFunc(motion);
	glutTimerFunc(0, FPS, 0);
	glutPassiveMotionFunc(passive);
}

// main function - program entry point
int main(int argc, char** argv)
{
	srand(time(NULL));
	std::cout<<instruction<<std::endl;
	glutInit(&argc, argv);		
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	glutInitWindowSize(s_width, s_height);
	glutInitWindowPosition(500, 100);
	glutCreateWindow("Assignment 2");	//creates the window
	gluOrtho2D(0,s_width,0,s_height);	//change window coordinate 
    
	createPaticles();			//create random number particles
	callBackInit();
	glutMainLoop();				//starts the event glutMainLoop
	return(0);					//return may not be necessary on all compilers
}