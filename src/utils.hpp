#include <raymath.h>
#include <math.h>

#ifndef UTILS_HPP
#define UTILS_HPP

#define L_NAN_VECTOR2 Vector2{NAN, NAN}
#define NULL_LRAY LRay(Vector2{NAN, NAN}, Vector2{NAN, NAN}, false, BLACK)

template<typename T> int sgn(T v) {
  return (v < 0) ? -1 : ((v > 0) ? 1 : 0);
}

float getAngleBetween(Vector2 p0, Vector2 p1){

    auto delta = Vector2Subtract(p0, p1);
    float m = -delta.y / delta.x;
    float angle = atan(m);

    if(delta.x < 0.0) angle += PI; else if(delta.x == 0) angle = -M_PI_2 * (float)sgn(delta.y);

    return angle;
}

#endif