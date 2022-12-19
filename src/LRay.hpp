#include <raymath.h>
#include <raylib.h>
#include <tuple>
#include <utility>
#include <memory>
#include "utils.hpp"

#ifndef LRAY_HPP
    #define LRAY_HPP
    #define LRAYNULLPTR (Ray*) nullptr

namespace L{
class Ray{

    public:
        Vector2 start;
        Vector2 end;
        bool isObstacle;
        float length;
        Color renderColor;



        void adjustAngle(float);
        float pointTo(Vector2);
        std::tuple<bool, Vector2> getLineIntersection(Ray&);
        std::tuple<bool,Vector2, std::shared_ptr<Ray>> getSegmentIntersection(Ray&);
        void updateLength(Ray&);
        std::shared_ptr<Ray> getCollidingCurrent();
        void render();
        
        Ray();
        Ray(Vector2, Vector2, bool, Color);
        Ray(Vector2, float, float, bool, Color);
        ~Ray();


        private:
            std::shared_ptr<Ray> collidingCurrent;


};   


Ray::Ray(){}

Ray::Ray(Vector2 start, Vector2 end, bool isObstacle = false, Color renderColor = BLACK){

    
    this -> start = start;
    this -> end = end;
    this -> length = Vector2Distance(start,end);
    this -> renderColor = renderColor;
    this -> collidingCurrent = std::make_shared<Ray>(LRAYNULLPTR);
    this -> isObstacle = isObstacle;

}

Ray::Ray(Vector2 start, float length = 0.f, float angle = 0.f, bool isObstacle = false, Color renderColor = BLACK){

    Vector2 end = Vector2{cos(angle) * length, -sin(angle) * length};

    this -> length = length;
    this -> start = start;
    this -> end = end;
    this -> isObstacle = isObstacle;
    this -> renderColor = renderColor;
    this -> collidingCurrent = std::make_shared<Ray>(LRAYNULLPTR);

}

Ray::~Ray(){



}


std::shared_ptr<Ray> Ray::getCollidingCurrent(){

    return this -> collidingCurrent;

}





void Ray::adjustAngle(float angle){


    this -> end = Vector2Add(this -> start, Vector2{cos(angle) * this -> length, -sin(angle) * this -> length});
}


float Ray::pointTo(Vector2 target){

    Vector2 deltaPos = Vector2Subtract(target, this -> start);
    const float m = -deltaPos.y / deltaPos.x;
    float angle = atan(m);

    if(deltaPos.x < 0.f){

        angle += PI;
        
    }else if(deltaPos.x == 0.f){

        angle = -M_PI_2;
    }

    this -> end = Vector2Add(this -> start, Vector2{cos(angle) * this -> length, -sin(angle) * this -> length});

    return angle;

}

std::tuple<bool, Vector2> Ray::getLineIntersection(Ray& target){

    if(!target.isObstacle) return std::make_tuple(false, L_NAN_VECTOR2);

    bool isIntersecting = false;

    float a1 = this -> start.y - this -> end.y;
    float b1 = this -> end.x - this -> start.x;
    float c1 = a1 * this -> end.x + b1 * this -> end.y;

    float a2 = target.start.y - target.end.y;
    float b2 = target.end.x - target.start.x;
    float c2 = a2 * target.end.x + b2 * target.end.y;

    float den = a1 * b2 - a2 * b1;

    if( den != 0.f ){

        isIntersecting = true;

    }

    return std::make_tuple(isIntersecting, Vector2{(b2 * c1 - b1 * c2) / den, (a1 * c2 - a2 * c1) / den});
}

std::tuple<bool, Vector2, std::shared_ptr<Ray>> Ray::getSegmentIntersection(Ray& target){

    

    if(!target.isObstacle)
    {
        
        this -> collidingCurrent = std::make_shared<Ray>(LRAYNULLPTR);   
        return std::make_tuple(false, L_NAN_VECTOR2, this -> collidingCurrent);

    }

    Vector2 intersection = std::get<1>(this -> getLineIntersection(target));

    Vector2 r0 = Vector2{(intersection.x - this -> end.x) / ( this -> start.x - this -> end.x ), (intersection.y - this -> end.y) / ( this -> start.y - this -> end.y)};
    Vector2 r1 = Vector2{(intersection.x -  target.end.x) / ( target.start.x -  target.end.x ), (intersection.y -  target.end.y) / ( target.start.y - target.end.y)};

    if(((r0.x > 0.0 && r0.x < 1.0) || (r0.y > 0.0 && r0.y < 1.0)) && ((r1.x > 0.0 && r1.x < 1.0) || (r1.y > 0.0 && r1.y < 1.0))){

        this -> collidingCurrent = std::make_shared<Ray>(target);

        return std::make_tuple(true, intersection, this -> collidingCurrent);

    }else{

        this -> collidingCurrent = std::make_shared<Ray>(LRAYNULLPTR);
        return std::make_tuple(false, L_NAN_VECTOR2, this -> collidingCurrent);
        
    }
    
    
}

void Ray::updateLength(Ray& obstacle){

    auto intersectionInfo = this -> getSegmentIntersection(obstacle);
    Vector2 intersectionPos = std::get<1>(intersectionInfo);

    if(Vector2Distance(this -> end, intersectionPos) <= this -> length && std::get<0>(intersectionInfo)){

        this -> end = intersectionPos;

    }

    

}

void Ray::render(){

    DrawLineV(this -> start, this -> end, this -> renderColor);

}

}

#endif

