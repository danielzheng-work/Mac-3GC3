#include <math.h>
#include "mathLib2D.h"
#include "particle2D.h"
#include <cstdlib>
Particle2D::Particle2D(){
        float pX = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float pY = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        Position = Point2D (pX, pY);
        red = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	green = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	blue = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        /*red = rand() %300;
        green = rand()%300;
        blue = rand()%300;*/
        size = rand() % 10 + 1;
        Direction= Vec2D(0.0f,0.0f);
        range = (rand()) / (RAND_MAX/100);
        speed = 5;
};


