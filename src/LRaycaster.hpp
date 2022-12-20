#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <utility>
#include <memory>
#include <iostream>
#include "LRay.hpp"




#ifndef LRAYCASTER_HPP
    #define LRAYCASTER_HPP

#define DEFAULT_HITBOX_SIZE 10.f

namespace L{

//Class which represents a collection of Rays that act like a collectiveness.

class RayCaster{

    public:

        Vector2 position;
        float rayLength;
        Color renderColor;
        std::vector<std::shared_ptr<L::Ray>> rays;
        
        float fov;

        void constrainTo(Rectangle);
        void pointTo(Vector2);
        void follow(Vector2, float, float);
        std::vector<float> getRaysIntersectionDistance();
        std::shared_ptr<L::Ray> getCollidingAt(int);
        void update(std::shared_ptr<L::Ray>);
        void update(std::vector<std::shared_ptr<L::Ray>>);
        void render();
        void resetCollisions();

        RayCaster(Vector2, float, float, float, float, Color);
        RayCaster(Vector2, float, float, int, float, Color);
        ~RayCaster();


    private:

        float hitboxSize;
        float startingAngle;
        Vector2 velocity;
        



};

//Constructor.
RayCaster::RayCaster(Vector2 position, float startingAngle = M_PI_2, float fov = 60.f, int nRays = 100, float rayLength = 50.f, Color renderColor = BLACK){

    float focalLength = (1.f / tan(fov / 2.f));
    float x = 0.f;
    float tAngle;
    float angle = startingAngle - (fov / 2.f);

    for(int i = 0; i < nRays; ++i){
        
        x = .5f - ((float) i / (float) nRays);
        tAngle = atan2(x, focalLength);
        
        L::Ray r = L::Ray(position, rayLength, angle + tAngle,false,renderColor);
        this -> rays.push_back( std::make_shared<L::Ray>(r) );

    }

   this -> position = position;
   this -> rayLength = rayLength;
   this -> renderColor = renderColor;
   this -> hitboxSize = DEFAULT_HITBOX_SIZE;
   this -> startingAngle = startingAngle; 
   this -> fov = fov;
   this -> velocity = Vector2{0.f, 0.f};


}

//Destructor.
RayCaster::~RayCaster(){
}


//Constrains the caster to some given boundaries.
void RayCaster::constrainTo(Rectangle boundaries){

    if(!CheckCollisionPointRec(this -> position, boundaries)){

        this -> position = Vector2Subtract(this -> position, this -> velocity);

    }


}

//Updates the angle of all the rays to make the caster to look at a given position.
void RayCaster::pointTo(Vector2 target){

    float angle = getAngleBetween(this -> position, target);
    float focalLength = (1.f / tan(this -> fov / 2.f)) / 2.f;
    float x = 0;
    float tAngle;

    for(int i = 0; i < this -> rays.size(); ++i){

        x = .5f - ((float) i / (float) this -> rays.size());
        tAngle = atan2(x, focalLength);
        this -> rays[i] -> adjustAngle(angle + tAngle + PI);
    }
}

//Makes the caster follow a given position and move until it reaches the position minus the offset.
void RayCaster::follow(Vector2 target, float offset, float deltaTime){

    float distance = Vector2Distance(this -> position, target);

    distance = std::max(distance - offset, 0.f);
    distance /= 1.f;

    float angle = getAngleBetween(this -> position, target);

    this -> velocity = Vector2Multiply(Vector2{distance * -cos(angle), distance * sin(angle)}, Vector2{deltaTime, deltaTime});
    this -> position = Vector2Add(this -> position, this -> velocity);

    for(auto& ray : this -> rays){

        ray -> start = this -> position;

    }

}

//Returns the length of every ray.
std::vector<float> RayCaster::getRaysIntersectionDistance(){

    std::vector<float> distances;

    for(auto& ray : this -> rays){

        distances.push_back(Vector2Distance(ray -> start, ray -> end));

    }

    return distances;
}   


//Returns the colliding ray of a given ray.
std::shared_ptr<L::Ray> RayCaster::getCollidingAt(int index){

    

    return this-> rays[index] -> getCollidingCurrent();

}

//Updates every ray of the caster.
void RayCaster::update(std::shared_ptr<L::Ray> obstacle){

    for(auto& ray : this -> rays){

        ray -> updateLength( obstacle );

        

    }

}

//Updates the caster.
void RayCaster::update(std::vector<std::shared_ptr<L::Ray>> obstacles){

    for(auto& obstacle : obstacles){

        for(auto& ray: this -> rays){


            ray -> updateLength( obstacle );

        }


    }


}

//Resets caster's collisions.
void RayCaster::resetCollisions(){

    for(int i = 0; i < this -> rays.size(); ++i){

        this -> rays[i] -> resetColliding();

    }

}

//Renders the caster.
void RayCaster::render(){


    for(auto& ray : this -> rays){

        ray -> render();

    }

}

    typedef RayCaster Caster;
    typedef RayCaster Camera;

}
#endif