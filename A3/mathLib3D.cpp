#include <math.h>
#include "mathLib3D.h"

// Implement functions here.

// Don't write a main function, do that in main.cpp
Point3D::Point3D(): Point3D(0.0f, 0.0f, 0.0f) {}
Point3D::Point3D(float inX, float inY, float inZ) {
	mX = inX;
	mY = inY;
	mZ = inZ;
}

float Point3D::distanceTo(Point3D other)
{
    float  x1 {mX};
    float  y1 {mY};
    float  z1 {mZ};
    float  x2 {other.mX};
    float  y2 {other.mY};
    float  z2 {other.mZ};
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1 -z2)*(z1-z2));

}

float Point3D::fastDistanceTo(Point3D other)
{
    float  x1 {mX};
    float  y1 {mY};
    float  z1 {mZ};
    float  x2 {other.mX};
    float  y2 {other.mY};
    float  z2 {other.mZ};
    return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1 -z2)*(z1-z2);

}

Vec3D::Vec3D(): Vec3D(0.0f, 0.0f, 0.0f) {}

Vec3D::Vec3D(float inX, float inY, float inZ) {
	mX = inX;
	mY = inY;
	mZ = inZ;
}

float Vec3D::length()
{
    return sqrt(mX*mX+mY*mY+mZ*mZ);
}

Vec3D Vec3D::normalize()
{
    float new_mX = (mX)/(length());
    float new_mY = (mY)/(length());
    float new_mZ = (mZ)/(length());
    return Vec3D(new_mX,new_mY, new_mZ);
}

Vec3D Vec3D::multiply(float scalar)
{
    float new_mX = scalar * mX;
    float new_mY = scalar * mY;
    float new_mZ = scalar * mZ;
    return Vec3D(new_mX,new_mY, new_mZ);

}

Point3D Vec3D::movePoint(Point3D source)// need to make new points to move
{
    float new_mX = source.mX + mX;
    float new_mY = source.mY + mY;
    float new_mZ = source.mZ + mZ;
    return Point3D(new_mX, new_mY, new_mZ);
}

Vec3D Vec3D::createVector(Point3D p1, Point3D p2)
{
    return Vec3D((p1.mX-p2.mX),(p1.mY-p2.mY),(p1.mZ-p2.mZ));
}
