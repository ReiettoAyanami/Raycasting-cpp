#include <raymath.h>
#include <math.h>

#ifndef UTILS_HPP
#define UTILS_HPP

#define L_NAN_VECTOR2 Vector2{NAN, NAN}
#define NULL_LRAY LRay(Vector2{NAN, NAN}, Vector2{NAN, NAN}, false, BLACK)

// Returns the sign of a number.
template<typename T> int sgn(T v) {
  return (v < 0) ? -1 : ((v > 0) ? 1 : 0);
}


// Returns the angle between 2 given positions.
float getAngleBetween(Vector2 p0, Vector2 p1){

    auto delta = Vector2Subtract(p0, p1);
    float m = -delta.y / delta.x;
    float angle = atan(m);

    if(delta.x < 0.0) angle += PI; else if(delta.x == 0) angle = -M_PI_2 * (float)sgn(delta.y);

    return angle;
}


// from rosettacode.
template<typename tVal>
tVal map_value(std::pair<tVal,tVal> a, std::pair<tVal, tVal> b, tVal inVal)
{
  tVal inValNorm = inVal - a.first;
  tVal aUpperNorm = a.second - a.first;
  tVal normPosition = inValNorm / aUpperNorm;

  tVal bUpperNorm = b.second - b.first;
  tVal bValNorm = normPosition * bUpperNorm;
  tVal outVal = b.first + bValNorm;

  return outVal;
}


#endif


