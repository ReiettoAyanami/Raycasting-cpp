#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <utility>
#include "LRay.hpp"

#define DEFAULT_HITBOX_SIZE 10.f

class LRayCaster{

    public:

        Vector2 position;
        float rayLength;
        Color renderColor;
        std::vector<LRay> rays;
        float step;

        void constrainTo(Rectangle);

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

        this -> rays.push_back(LRay{position,rayLength, angle, false, renderColor});

    }

   this -> position = position;
   this -> rayLength = rayLength;
   this -> renderColor = renderColor;
   this -> hitboxSize = DEFAULT_HITBOX_SIZE;
   this -> startingAngle = startingAngle; 
   this -> step = step;
   this -> velocity = Vector2{0.f, 0.f};


}

void LRayCaster::constrainTo(Rectangle boundaries){

    if(!CheckCollisionPointRec(this -> position, boundaries)){

        

    }


}