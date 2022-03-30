#ifndef POINT_3D_H
#define POINT_3D_H

#include <math.h>
#include "mathLib3D.h"


class Particle3D {
public:
	
	Particle3D();
	Point3D Position;
	float red;
	float blue;
	float green; 
	float size;
	Vec3D Direction;

	int rot_Angle[3];
	float speed;
	int material; 
	int age;
};

#endif