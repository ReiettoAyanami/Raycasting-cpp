#include "LRay.hpp"
#include "LRaycaster.hpp"
#include "utils.hpp"
#include <iostream>
#include <algorithm>

#ifndef LRENDERER_HPP
    #define  LRENDERER_HPP
#define RAY_LENGTH_SHADOW_MODIFIER 0.1

namespace L{
    class Renderer{

        public:
            Renderer(L::RayCaster&, Rectangle);
            ~Renderer();

            void render();

        private:
            L::RayCaster& camera;
            Rectangle renderRegion;

            void renderRectangleAtScan(int, int, Color);

            



    };

    Renderer::Renderer(L::RayCaster& camera, Rectangle renderRegion):camera(camera){

        this -> renderRegion = renderRegion;

    }


    Renderer::~Renderer(){



    }


    void Renderer::renderRectangleAtScan(int scanIdx, int scanHeight, Color renderColor){

        float scanWidth = this -> renderRegion.width / this -> camera.rays.size();
        DrawRectangle(((int) scanWidth * scanIdx) + (int)this -> renderRegion.x, (int)((this -> renderRegion.y + this -> renderRegion.height)/2.f) - scanHeight / 2, (int) scanWidth, scanHeight, renderColor);

    }

    void Renderer::render(){

        auto step = this -> camera.step;
        auto fov = this -> camera.step * (float) this -> camera.rays.size();
        //auto rays = this -> camera.getRaysIntersectionDistance();

        

        for(int i = 0; i < this -> camera.rays.size(); ++i){

            float fixedDistance = Vector2Distance(this -> camera.rays[i]->start,this->camera.rays[i]->end ) * cos(  ((fov / 2.f) - (this -> camera.step) * (float)i) );
            float rectangleHeight = this -> renderRegion.height - fixedDistance;

            
            Color renderColor;


            std::cout << camera.rays[i]->getCollidingCurrent() << std::endl;

            if(this -> camera.rays[i]->getCollidingCurrent() != nullptr){

                Color collidingRenderColor = this -> camera.rays[i]->getCollidingCurrent()->renderColor;
                Quaternion collidingQuaternion = ColorNormalize(collidingRenderColor);


                Quaternion normalizedColor = QuaternionNormalize(Vector4{std::min(1.f, (float)(collidingQuaternion.x / (Vector2Distance(this -> camera.rays[i] -> start, this -> camera.rays[i] -> end) * RAY_LENGTH_SHADOW_MODIFIER))),std::min(1.f, (float)(collidingQuaternion.y / (Vector2Distance(this -> camera.rays[i] -> start, this -> camera.rays[i] -> end) * RAY_LENGTH_SHADOW_MODIFIER))),std::min(1.f, (float)(collidingQuaternion.z / (Vector2Distance(this -> camera.rays[i] -> start, this -> camera.rays[i] -> end) * RAY_LENGTH_SHADOW_MODIFIER))),1.f});
                renderColor = ColorFromNormalized(normalizedColor);
            
            }else{

                renderColor = Color{0,255,0,255};

            }


            this -> renderRectangleAtScan(i, rectangleHeight, renderColor);


        }
    

    }
}

#endif