#include "LRay.hpp"
#include <raylib.h>
#include <iostream>
#include <vector>
#include <memory>

#ifndef LWALL_HPP

    #define LWALL_HPP

#define DEFAULT_WALL_THICKNESS 10.f

namespace L{

class Wall{

    public:
        std::vector<std::shared_ptr<Ray>> obstacles;

        void render();

        Wall(Vector2, float, float, float, Color);
        Wall();
        ~Wall();
        
};

Wall::Wall(){}
Wall::~Wall(){}

Wall::Wall(Vector2 position, float width = DEFAULT_WALL_THICKNESS, float height = DEFAULT_WALL_THICKNESS, float angle = M_PI_2, Color renderColor = BLACK){

    Ray p1 = Ray{position, width, angle, true, renderColor};
    
    // Ray p2 = Ray(Vector2{position.x, position.y + height}, width, angle, true, renderColor);
    // Ray p3(p1.start, p2.start, true, renderColor);
    // Ray p4(p1.end, p2.end, true, renderColor);

    

    this -> obstacles.push_back(std::make_shared<Ray>(p1));
    //this -> obstacles.push_back(std::make_shared<Ray>(p2));
    // this -> obstacles.push_back(std::make_shared<Ray>(p3));
    // this -> obstacles.push_back(std::make_shared<Ray>(p4));
}

void Wall::render(){

    for(auto& obstacle : this -> obstacles){

        obstacle -> render();

    }

}

}




#endif