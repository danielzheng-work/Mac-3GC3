#ifndef POINT_2D_H
#define POINT_2D_H

#include <math.h>
#include "mathLib2D.h"


class Particle2D {
public:
	
	Particle2D();
	Point2D Position;
	float red;
	float blue;
	float green; // vaiables to represent the colour of particles
	int size;
	Vec2D Direction;
	int range;
	float speed;
	
};

#endif