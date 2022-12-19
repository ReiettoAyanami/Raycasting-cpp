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

class RayCaster{

    public:

        Vector2 position;
        float rayLength;
        Color renderColor;
        std::vector<std::shared_ptr<L::Ray>> rays;
        float step;

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
        ~RayCaster();


    private:

        float hitboxSize;
        float startingAngle;
        Vector2 velocity;
        



};

RayCaster::RayCaster(Vector2 position, float startingAngle = M_PI_2, float fov = 60.f, float step = 1.f, float rayLength = 50.f, Color renderColor = BLACK){

    
    const long int numIterations = (long int)(fov / step);

    for(int i = 0; i < numIterations; ++i){

        float angle = startingAngle - (step * (float)i);
        L::Ray tempRay = L::Ray{position,rayLength, angle, false, renderColor};
        this -> rays.push_back(std::make_shared<L::Ray>(tempRay));

    }

   this -> position = position;
   this -> rayLength = rayLength;
   this -> renderColor = renderColor;
   this -> hitboxSize = DEFAULT_HITBOX_SIZE;
   this -> startingAngle = startingAngle; 
   this -> step = step;
   this -> velocity = Vector2{0.f, 0.f};


}

RayCaster::~RayCaster(){
}

void RayCaster::constrainTo(Rectangle boundaries){

    if(!CheckCollisionPointRec(this -> position, boundaries)){

        this -> position = Vector2Subtract(this -> position, this -> velocity);

    }


}

void RayCaster::pointTo(Vector2 target){

    float fov = this -> step * ((float)(this -> rays.size()) - 1.f);
    float relativeAngle = fov / 2.f;

    for(auto& ray : this -> rays){

        float angle = relativeAngle + getAngleBetween(target, ray -> start);
        relativeAngle -= this -> step;
        ray -> adjustAngle(angle);

    }

}

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

std::vector<float> RayCaster::getRaysIntersectionDistance(){

    std::vector<float> distances;

    for(auto& ray : this -> rays){

        distances.push_back(Vector2Distance(ray -> start, ray -> end));

    }

    return distances;
}   

std::shared_ptr<L::Ray> RayCaster::getCollidingAt(int index){

    

    return this-> rays[index] -> getCollidingCurrent();

}

void RayCaster::update(std::shared_ptr<L::Ray> obstacle){

    for(auto& ray : this -> rays){

        ray -> updateLength( obstacle );

        

    }

}

void RayCaster::update(std::vector<std::shared_ptr<L::Ray>> obstacles){

    for(auto& obstacle : obstacles){

        for(auto& ray: this -> rays){


            ray -> updateLength( obstacle );

        }


    }


}

void RayCaster::resetCollisions(){

    for(int i = 0; i < this -> rays.size(); ++i){

        this -> rays[i] -> resetColliding();

    }

}

void RayCaster::render(){


    for(auto& ray : this -> rays){

        ray -> render();

    }

}
}
#endif