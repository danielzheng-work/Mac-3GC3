#include "mathLib2D.h"
#include <iostream>

int main() {
    Point2D p1(3.0,4.0);
    Point2D p2(5.0,12.0);
    Point2D p3(9.0,12.0);
    Vec2D   v1(1.0,2.0);
    Vec2D   v2(6.0,8.0);
    Vec2D   v3(10.0,10.0);

    std::cout<< " First  test case:two point distance is "<<p1.distanceTo(p2)<<std::endl;
    std::cout<< " Second test case:two point distance is "<<p2.distanceTo(p3)<<std::endl;
    std::cout<< " Third  test case:two point distance is "<<p1.distanceTo(p3)<<std::endl;

    std::cout<< " First  test case:two point faster distance is "<<p1.fastDistanceTo(p2)<<std::endl;
    std::cout<< " Second test case:two point faster distance is "<<p2.fastDistanceTo(p3)<<std::endl;
    std::cout<< " Third  test case:two point faster distance is "<<p1.fastDistanceTo(p3)<<std::endl;
    
    std::cout<< " First  test case: vector length is "<<v1.length()<<std::endl;
    std::cout<< " Second test case: vector length is "<<v2.length()<<std::endl;
    std::cout<< " Third  test case: vector length is "<<v3.length()<<std::endl;

    std::cout<< " First  test case: vector after normalize: norm_x = "<<(v1.normalize()).mX<<",norm_y= "<<(v1.normalize()).mY<<std::endl;
    std::cout<< " Second test case: vector after normalize: norm_x = "<<(v3.normalize()).mX<<",norm_y= "<<(v3.normalize()).mY<<std::endl;

    std::cout<< " First  test case: vector after multiply : x = "<<(v2.multiply(2.0)).mX<<",y= "<<(v2.multiply(2.0)).mY<<std::endl;
    std::cout<< " Second test case: vector after multiply : x = "<<(v3.multiply(0.5)).mX<<",y= "<<(v3.multiply(0.5)).mY<<std::endl;

    std::cout<< " First  test case: vector after moving : x = "<<(v1.movePoint(p1)).mX<<",y= "<<(v1.movePoint(p1)).mY<<std::endl;
    std::cout<< " Second test case: vector after moving : x = "<<(v1.movePoint(p2)).mX<<",y= "<<(v1.movePoint(p2)).mY<<std::endl;

    std::cout<< " First test case: create new vector: x= "<<(v1.createVector(p3,p2)).mX<<",y= "<<(v1.createVector(p3,p2)).mY<<std::endl;
    std::cout<< " First test case: create new vector: x= "<<(v2.createVector(p3,p1)).mX<<",y= "<<(v2.createVector(p3,p1)).mY<<std::endl;



    return 0;
}
