#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <utility>
#include <memory>
#include <iostream>
#include "LRay.hpp"
#include "LWall.hpp"




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
        std::vector<std::shared_ptr<Ray>> rays;
        float fov;

        void constrainTo(Rectangle);
        void pointTo(Vector2);
        void follow(Vector2, float, float);
        std::vector<float> getRaysIntersectionDistance();
        std::shared_ptr<Ray> getCollidingAt(int);
        void update(std::shared_ptr<Ray>);
        void update(std::vector<std::shared_ptr<Ray>>);
        void update(std::shared_ptr<Wall>);
        void render();
        void resetCollisions();
        void move(KeyboardKey, Vector2, Vector2, float);
        void moveVisual(KeyboardKey, KeyboardKey, float);
        void moveVisual(float, float, float );
        void renderFOV();

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
        
        Ray r = Ray(position, rayLength, angle + tAngle,false,renderColor);
        this -> rays.push_back( std::make_shared<Ray>(r) );

    }

   this -> position = position;
   this -> rayLength = rayLength;
   this -> renderColor = renderColor;
   this -> hitboxSize = DEFAULT_HITBOX_SIZE;
   this -> startingAngle = startingAngle; 
   this -> fov = fov;
   this -> velocity = Vector2{0.f, 0.f};


}

//Destructor.renderingHeightMultiplier
RayCaster::~RayCaster(){
}


//Constrains the caster to some given boundaries.
void RayCaster::constrainTo(Rectangle boundaries){

    if(!CheckCollisionPointRec(this -> position, boundaries)){

        this -> position = Vector2Subtract(this -> position, this -> velocity);

    }


}

//Moves camera with two keys
void RayCaster::moveVisual(KeyboardKey left, KeyboardKey right, float step){

    bool l = IsKeyDown(left);
    bool r = IsKeyDown(right);


    for(auto& ray : this -> rays){

        ray -> adjustAngle(ray -> angle + (step * (float)l));
        ray -> adjustAngle(ray -> angle - (step * (float)r));

    }


}

//Moves visual based on x mouse position on the screen.
void RayCaster::moveVisual(float mousePos, float windowWidth, float maxOffset = PI * 2){

    
    
    float angleOffset = map_value<float>(std::make_pair(0.f, windowWidth), std::make_pair(0.f, maxOffset), mousePos);

    for(auto& ray : this -> rays){

        ray -> adjustAngle(ray -> angle + angleOffset);


    }


}

//Moves the caster in the 2D space.
void RayCaster::move(KeyboardKey up, Vector2 velocity, Vector2 mousePos, float offset){
    

    this -> velocity = Vector2{0.f, 0.f};

    if(Vector2Distance(this -> position, mousePos) >= offset){


        if(IsKeyDown(up)) this -> velocity = Vector2Multiply(velocity, Vector2{cos(this -> rays[this -> rays.size() / 2] -> angle), -sin(this -> rays[this -> rays.size() / 2] -> angle)});

        this -> position = Vector2Add(this -> position, this -> velocity);
    
    }

    for(auto& ray : this -> rays){

        ray -> start = Vector2Add(ray -> start, this -> velocity);
        ray -> end  = Vector2Add(ray -> end, this -> velocity);
        ray -> adjustAngle(ray -> angle);
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
std::shared_ptr<Ray> RayCaster::getCollidingAt(int index){

    

    return this-> rays[index] -> getCollidingCurrent();

}

//Updates every ray of the caster.
void RayCaster::update(std::shared_ptr<Ray> obstacle){

    for(auto& ray : this -> rays){

        ray -> updateLength( obstacle );

    }

}

//Updates the caster.
void RayCaster::update(std::vector<std::shared_ptr<Ray>> obstacles){

    for(auto& obstacle : obstacles){

        for(auto& ray: this -> rays){


            ray -> updateLength( obstacle );

        }


    }


}

void RayCaster::update(std::shared_ptr<Wall> wall){

    for(auto& obstacle : wall -> obstacles){

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

void RayCaster::renderFOV(){

    for(int i = 0; i < this -> rays.size() - 1; ++i){

        DrawLineV(this -> rays[i] -> end, this -> rays[i+1] -> end, this -> rays[i] -> renderColor);

    }

    this -> rays [0] -> render();
    this -> rays[this -> rays.size() - 1] -> render();

}

    typedef RayCaster Caster;
    typedef RayCaster Camera;

}
#endif