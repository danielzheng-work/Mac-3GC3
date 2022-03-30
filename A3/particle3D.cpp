#include <math.h>
#include "mathLib3D.h"
#include "particle3D.h"
#include <cstdlib>

Particle3D::Particle3D(){
        //spawn paticle in origin to start 
        Position = Point3D (0.0, 0.0, 0.0);

        // generate three float number between 0-1, for color
        red = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	green = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	blue = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        
        // genrate random size of particle between 0.5-2;
        size = (rand()% 4 + 1)/2;

        //set initial direction of particle
        float vecX = (rand() % 15 - 8);
	float vecY = (rand()%10 + 150);//max height particle can reach
	float vecZ = (rand() % 15 - 8);
        Direction= Vec3D(vecX, vecY, vecZ);

        //get random angle between 1-360 for rotate 
        rot_Angle[0] = rand()%360+1;
        rot_Angle[1] = rand()%360+1;
        rot_Angle[2] = rand()%360+1;

        speed = rand()% 5 + 1;
        //material type: 0, 1,2
        material = rand()%3;
        //lifespan between 180-279
        int age = rand()%100 + 180;
}
