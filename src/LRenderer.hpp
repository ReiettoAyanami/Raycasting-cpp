#include "LRay.hpp"
#include "LRaycaster.hpp"
#include "utils.hpp"
#include <memory>
#include <iostream>
#include <algorithm>

#ifndef LRENDERER_HPP
    #define  LRENDERER_HPP
    
#define RAY_LENGTH_SHADOW_MODIFIER .06
#define NULL_RES_COLOR Color{0,0,0,0}
#define CONST_WALL_H 12000

namespace L{

    //A class which renders a Casters pov.
    class Renderer{

        public:
            Renderer(std::shared_ptr<L::RayCaster>, Rectangle);
            ~Renderer();

            void render();

        private:
            std::shared_ptr<L::RayCaster> camera;
            Rectangle renderRegion;

            void renderRectangleAtScan(int, int, Color);

            



    };
    //Constructor.
    Renderer::Renderer(std::shared_ptr<L::RayCaster> camera, Rectangle renderRegion){

        this -> renderRegion = renderRegion;
        this -> camera = camera;

    }

    //Destructor.
    Renderer::~Renderer(){



    }

    //Render a Rectangle at a given scan.
    void Renderer::renderRectangleAtScan(int scanIdx, int scanHeight, Color renderColor){

        float scanWidth = this -> renderRegion.width / this -> camera -> rays.size();
        DrawRectangle(((int) scanWidth * scanIdx) + (int)this -> renderRegion.x, (int)((this -> renderRegion.y + this -> renderRegion.height)/2.f) - scanHeight / 2, (int) scanWidth, scanHeight, renderColor);

    }


    //Renders the whole camera pov.
    void Renderer::render(){

        

        for(int i = 0; i < this -> camera -> rays.size(); ++i){
            
            float focalAngle = this -> camera -> rays[i] -> angle -(this -> camera -> rays[0] -> angle - (this -> camera -> fov / 2.f));

            float fixedDistance = Vector2Distance(this -> camera -> rays[i]->start,this->camera -> rays[i]->end ) * cos( focalAngle );
            float rectangleHeight = CONST_WALL_H / fixedDistance;

            
            Color renderColor;

            if(this -> camera -> rays[i]->getCollidingCurrent() != nullptr){

                Color collidingRenderColor = this -> camera -> rays[i]->getCollidingCurrent()->renderColor;
                Quaternion collidingQuaternion = ColorNormalize(collidingRenderColor);


                Quaternion normalizedColor = QuaternionNormalize(Vector4{std::min(1.f, (float)(collidingQuaternion.x / (Vector2Distance(this -> camera -> rays[i] -> start, this -> camera -> rays[i] -> end) * RAY_LENGTH_SHADOW_MODIFIER))),std::min(1.f, (float)(collidingQuaternion.y / (Vector2Distance(this -> camera -> rays[i] -> start, this -> camera -> rays[i] -> end) * RAY_LENGTH_SHADOW_MODIFIER))),std::min(1.f, (float)(collidingQuaternion.z / (Vector2Distance(this -> camera -> rays[i] -> start, this -> camera -> rays[i] -> end) * RAY_LENGTH_SHADOW_MODIFIER))),1.f});
                renderColor = ColorFromNormalized(normalizedColor);
            
            }else{

                renderColor = NULL_RES_COLOR;
                

            }


            this -> renderRectangleAtScan(i, rectangleHeight, renderColor);


        }
    

    }

}

#endif