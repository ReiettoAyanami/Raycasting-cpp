#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <utility>
#include "LRay.hpp"


#ifndef LRAYCASTER_HPP
#define LRAYCASTER_HPP

#define DEFAULT_HITBOX_SIZE 10.f



class LRayCaster{

    public:

        Vector2 position;
        float rayLength;
        Color renderColor;
        std::vector<LRay*> rays;
        float step;


        void constrainTo(Rectangle);
        void pointTo(Vector2);
        void follow(Vector2, float, float);
        std::vector<float> getRaysIntersectionDistance();
        LRay* getCollidingAt(int);
        void update(LRay&);
        void render();


        LRayCaster(Vector2, float, float, float, float, Color);
        ~LRayCaster();


    private:

        float hitboxSize;
        float startingAngle;
        Vector2 velocity;
        



};

LRayCaster::LRayCaster(Vector2 position, float startingAngle = M_PI_2, float fov = 60.f, float step = 1.f, float rayLength = 50.f, Color renderColor = BLACK){

    
    const long int numIterations = (long int)(fov / step);

    for(int i = 0; i < numIterations; ++i){

        float angle = startingAngle - (step * (float)i);
        LRay* tempRay = new LRay{position,rayLength, angle, false, renderColor};
        this -> rays.push_back(tempRay);

    }

   this -> position = position;
   this -> rayLength = rayLength;
   this -> renderColor = renderColor;
   this -> hitboxSize = DEFAULT_HITBOX_SIZE;
   this -> startingAngle = startingAngle; 
   this -> step = step;
   this -> velocity = Vector2{0.f, 0.f};


}

LRayCaster::~LRayCaster(){
}

void LRayCaster::constrainTo(Rectangle boundaries){

    if(!CheckCollisionPointRec(this -> position, boundaries)){

        this -> position = Vector2Subtract(this -> position, this -> velocity);

    }


}

void LRayCaster::pointTo(Vector2 target){

    float fov = this -> step * ((float)(this -> rays.size()) - 1.f);
    float relativeAngle = fov / 2.f;

    for(auto& ray : this -> rays){

        float angle = relativeAngle + getAngleBetween(target, ray -> start);
        relativeAngle -= this -> step;
        ray -> adjustAngle(angle);

    }

}

void LRayCaster::follow(Vector2 target, float offset, float deltaTime){

    float distance = Vector2Distance(this -> position, target);

    distance = std::max(distance - offset, 0.f);
    distance /= 1.f;

    float angle = getAngleBetween(this -> position, target);

    this -> velocity = Vector2Multiply(Vector2{distance - acos(angle), distance * sin(angle)}, Vector2{deltaTime, deltaTime});
    this -> position = Vector2Add(this -> position, this -> velocity);

    for(auto& ray : this -> rays){

        ray -> start = this -> position;

    }

}

std::vector<float> LRayCaster::getRaysIntersectionDistance(){

    std::vector<float> distances;

    for(auto& ray : this -> rays){

        distances.push_back(Vector2Distance(ray -> start, ray -> end));

    }

    return distances;
}   

LRay* LRayCaster::getCollidingAt(int index){

    return this-> rays[index] -> getCollidingCurrent();

}

void LRayCaster::update(LRay& obstacle){

    for(auto& ray : this -> rays){

        ray -> updateLength( obstacle );

    }

}

void LRayCaster::render(){


    for(auto& ray : this -> rays){

        ray -> render();

    }

}

#endif