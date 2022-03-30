#include <math.h>
#include "mathLib2D.h"

// Implement functions here.

// Don't write a main function, do that in main.cpp
Point2D::Point2D(): mX(0.0f), mY(0.0f){};

Point2D::Point2D(float inX, float inY): mX(inX), mY(inY){};

float Point2D::distanceTo(Point2D other)
{
    float  x1 {mX};
    float  y1 {mY};
    float  x2 {other.mX};
    float  y2 {other.mY};
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));

};

float Point2D::fastDistanceTo(Point2D other)
{
    float  x1 {mX};
    float  y1 {mY};
    float  x2 {other.mX};
    float  y2 {other.mY};
    return ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));

};

Vec2D::Vec2D(): mX(0.0f), mY(0.0f){};

Vec2D::Vec2D(float inX, float inY): mX(inX), mY(inY){};

float Vec2D::length()
{
    return sqrt((mX*mX+mY*mY));
};

Vec2D Vec2D::normalize()
{
    float new_mX = (mX)/(length());
    float new_mY = (mY)/(length());
    return Vec2D(new_mX,new_mY);
};

Vec2D Vec2D::multiply(float scalar)
{
    float new_mX = scalar * mX;
    float new_mY = scalar * mY;
    return Vec2D(new_mX,new_mY);

};

Point2D Vec2D::movePoint(Point2D source)// need to make new points to move
{
    float new_mX = source.mX + mX;
    float new_mY = source.mY + mY;
    return Point2D(new_mX, new_mY);
};

Vec2D Vec2D::createVector(Point2D p1, Point2D p2)
{
    return Vec2D((p1.mX-p2.mX),(p1.mY-p2.mY));
}
